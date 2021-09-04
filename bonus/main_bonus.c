/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namina <namina@student.21-school.ru>         +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 19:10:19 by namina             #+#    #+#            */
/*   Updated: 2021/08/12 19:10:19 by namina            ###    #######.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child_process(t_list *params, int input_fd, int last_output_fd,
					   char **envp)
{
	t_list	*tmp;

	tmp = params;
	set_child_fd(params, input_fd, last_output_fd);
	execve(params->path_app, params->cmd_arr, envp);
	while (tmp->prev)
		tmp = tmp->prev;
	ft_lstclear(&tmp);
	exit(-1);
}

int	my_exec(t_list *params, int input_fd, int last_output_fd, char **envp)
{
	int		pid;
	int		fds[2];

	pipe(params->fd);
	pipe(fds);
	if (params->limiter)
	{
		get_input_from_std(params->limiter, fds[1]);
		close(fds[1]);
		input_fd = fds[0];
	}
	pid = fork();
	if (pid == 0)
		child_process(params, input_fd, last_output_fd, envp);
	else
	{
		waitpid(pid, NULL, WNOHANG);
		close(params->fd[1]);
		if (input_fd > 0)
			close(input_fd);
		if (!params->next)
			close(params->fd[0]);
	}
	return (params->fd[0]);
}

void	exec_manager(t_list *params, int input_fd,  int last_output_fd,
					 char **envp)
{
	while (params)
	{
		if (params->cmd_arr)
			input_fd = my_exec(params, input_fd, last_output_fd, envp);
		else
		{
			if (input_fd != -1)
			{
				close(input_fd);
				input_fd = -1;
			}
		}
		params = params->next;
	}
}

void	set_files_and_exec(t_list *params, char *input_file, char *output_file,
					char **envp)
{
	int		input_fd;
	int		last_output_fd;

	if (params->limiter)
		last_output_fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		last_output_fd = open(output_file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (last_output_fd == -1)
		perror(output_file);
	if (params->limiter)
		input_fd = -1;
	else
	{
		input_fd = open(input_file, O_RDONLY);
		if (input_fd == -1)
			perror(input_file);
	}
	exec_manager(params, input_fd, last_output_fd, envp);
	if (last_output_fd != -1)
		close(last_output_fd);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_list	*param_list;
	char	*input;
	char	*output_file;

	input = NULL;
	output_file = NULL;
	param_list = NULL;
	if (argc < 5)
		return (error_handle_argc());
	parser(&param_list, argv, &input, &output_file);
	if (validation(input, param_list, argc, envp) == -1)
	{
		ft_lstclear(&param_list);
		return (EXIT_FAILURE);
	}
	set_files_and_exec(param_list, input, output_file, envp);
	ft_lstclear(&param_list);
	return (0);
}
