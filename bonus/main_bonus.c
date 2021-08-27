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

#define TMP_FILE_NAME ".tmp.txt"

void	child_exec(t_list *params, int input_fd, int last_output_fd,
				   char **envp)
{
	char	**path_pointer;
	t_list	*list_top;

	params->path_arr = get_path_arr(envp);
	if (!params->path_arr)
		return ;
	set_path_arr(params->path_arr, params->cmd_arr[0]);
	path_pointer = params->path_arr;
	set_child_fd(params, input_fd, last_output_fd);
	while (*path_pointer)
	{
		execve(*path_pointer, params->cmd_arr, envp);
		path_pointer++;
	}
	list_top = params;
	while (list_top->prev)
		list_top = list_top->prev;
	error_handle_program(params->cmd_arr[0]);
	ft_lstclear(&list_top);
	exit(EXIT_FAILURE);
}

int	my_exec(t_list *params, int input_fd, int last_output_fd, char **envp)
{
	int		pid;
	int		exit_status;

	if (params->next)
		pipe(params->fd);
	pid = fork();
	if (pid == 0)
		child_exec(params, input_fd, last_output_fd, envp);
	else
	{
		wait(&exit_status);
		close(input_fd);
		if (params->limiter)
			unlink(TMP_FILE_NAME);
		if (params->next)
			close(params->fd[1]);
		if (WIFEXITED(exit_status) && WEXITSTATUS(exit_status))
			return (-1);
		if (params->next)
			return (params->fd[0]);
	}
	return (0);
}

int	exec_manager(t_list *params, char *input_file, char *output_file,
					char **envp)
{
	int		input_fd;
	int		last_output_fd;

	if (params->limiter)
	{
		input_fd = get_input_from_std(params->limiter);
		last_output_fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	}
	else
	{
		input_fd = open(input_file, O_RDONLY);
		last_output_fd = open(output_file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	}
	if (input_fd == -1 || last_output_fd == -1)
		return (-1);
	while (params)
	{
		input_fd = my_exec(params, input_fd, last_output_fd, envp);
		if (input_fd == -1)
			return (-1);
		params = params->next;
	}
	close(last_output_fd);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_list	*param_list;
	char	*input;
	char	*output_file;

	param_list = NULL;
	if (argc < 5)
		return (error_handle_argc());
	parser(&param_list, argv, &input, &output_file);
	envp++;
	if (validation(input, output_file, argc) == -1)
	{
		ft_lstclear(&param_list);
		return (EXIT_FAILURE);
	}
	if (exec_manager(param_list, input, output_file, envp) == -1)
	{
		ft_lstclear(&param_list);
		return (EXIT_FAILURE);
	}
	ft_lstclear(&param_list);
	return (0);
}
