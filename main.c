/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namina <namina@student.21-school.ru>         +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 19:10:19 by namina             #+#    #+#            */
/*   Updated: 2021/08/12 19:10:19 by namina            ###    #######.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_exec(t_list *params, int input_fd, int last_output_fd,
				   char **envp)
{
	char	**path_pointer;

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
//	ft_lstclear(&params); some shit here no comands
// valgrind ????
// make object
	error_handle_program(params->cmd_arr[0]);
	exit (EXIT_FAILURE);
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
	t_list	*tmp;
	int		input_fd;
	int		last_output_fd;

	input_fd = open(input_file, O_RDONLY);
	last_output_fd = open(output_file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (input_fd == -1 || last_output_fd == -1)
		return (-1);
	tmp = params;
	while (tmp)
	{
		input_fd = my_exec(tmp, input_fd, last_output_fd, envp);
		if (input_fd == -1)
		{
			close(last_output_fd);
			return (-1);
		}
		tmp = tmp->next;
	}
	close(last_output_fd);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_list	*param_list;
	char	*input_file;
	char	*output_file;

	param_list = NULL;
	if (argc != 5)
		return (error_handle_argc());
	parser(&param_list, argv, &input_file, &output_file);
	if (validation(input_file, output_file) == -1)
		return (ft_lstclear(&param_list));
	if (exec_manager(param_list, input_file, output_file, envp) == -1)
		return (ft_lstclear(&param_list));
	ft_lstclear(&param_list);
	return (0);
}
