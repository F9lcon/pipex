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

#include "pipex_bonus.h"

#define TMP_FILE_NAME ".tmp.txt"

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

int	validation(char *input_file, char *output_file, int argc)
{
	if (!input_file && argc < 6)
		return (error_handle_argc());
	if (input_file)
	{
		if (access(input_file, 0) == -1 || access(input_file, R_OK) == -1)
		{
			perror(input_file);
			return (-1);
		}
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

int	get_input_from_std(char *limiter)
{
	char	*line;
	int		tmp_file;

	line = NULL;
	tmp_file = open(TMP_FILE_NAME, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (tmp_file == -1)
		return (-1);
	while (get_next_line(STDIN_FILENO, &line) > 0)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1))
		{
			write(tmp_file, line, ft_strlen(line));
			write(tmp_file, "\n", 1);
		}
		else
			break ;
		free(line);
		line = NULL;
	}
	close(tmp_file);
	free(line);
	tmp_file = open(TMP_FILE_NAME, O_RDONLY, 0777);
	return (tmp_file);
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
	ft_putstr_fd("Need at least 4 args:\n", 2);
	ft_putstr_fd("file1 cmd1 ... cmdn file2\n", 2);
	ft_putstr_fd("For here_doc at least 5 args:\n", 2);
	ft_putstr_fd("here_doc LIMITER cmd cmd1 file\n", 2);
	ft_putstr_fd("------------------------------\n", 2);
	return (-1);
}
