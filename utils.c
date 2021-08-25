/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namina <namina@student.21-school.ru>         +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 14:38:56 by namina             #+#    #+#            */
/*   Updated: 2021/08/14 14:38:56 by namina            ###    #######.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	set_child_fd(t_list *params, int input_fd, int last_output_fd)
{
	dup2(input_fd, STDIN_FILENO);
	if (!(params->next))
		dup2(last_output_fd, STDOUT_FILENO);
	else
	{
		close(params->fd[0]);
		dup2(params->fd[1], STDOUT_FILENO);
	}
}

int	validation(char *input_file, char *output_file)
{
	if (access(input_file, 0) == -1 || access(input_file, R_OK) == -1)
	{
		perror(input_file);
		return (-1);
	}
	if (!access(output_file, 0))
	{
		if (access(output_file, W_OK) == -1)
		{
			perror(output_file);
			return (-1);
		}
	}
	return (0);
}

int	error_handle_program(char *app_name)
{
	ft_putstr_fd(app_name, 2);
	ft_putstr_fd(": No such program\n", 2);
	return (-1);
}

int	error_handle_argc(void)
{
	ft_putstr_fd("------------------------------\n", 2);
	ft_putstr_fd("Need 4 args:\n", 2);
	ft_putstr_fd("file1 cmd1 cmd2 file2\n", 2);
	ft_putstr_fd("------------------------------\n", 2);
	return (-1);
}
