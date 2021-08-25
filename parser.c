/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namina <namina@student.21-school.ru>         +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 13:13:04 by namina             #+#    #+#            */
/*   Updated: 2021/08/14 13:13:04 by namina            ###    #######.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#define PATH "PATH="

char	*get_path(char *absolute_path, char *app_name)
{
	char	*path;
	char	*path_pointer;

	path = ft_calloc(ft_strlen(absolute_path) + ft_strlen(app_name) + 2, 1);
	path_pointer = path;
	if (!path)
		exit(-1);
	while (*absolute_path)
	{
		*path_pointer = *absolute_path;
		path_pointer++;
		absolute_path++;
	}
	*path_pointer = '/';
	path_pointer++;
	while (*app_name)
	{
		*path_pointer = *app_name;
		path_pointer++;
		app_name++;
	}
	*path_pointer = '\0';
	return (path);
}

void	set_path_arr(char **current_path_arr, char *app_name)
{
	char	**path_arr;
	char	*prev_path;

	path_arr = current_path_arr;
	while (*path_arr)
	{
		prev_path = *path_arr;
		*path_arr = get_path(prev_path, app_name);
		free(prev_path);
		path_arr++;
	}
}

char	**get_path_arr(char **envp)
{
	char	**en;

	en = envp;
	while (*en)
	{
		if (ft_strnstr(*en, PATH, 5))
			return (ft_split((*en) + 5, ':'));
		en++;
	}
	return (NULL);
}

void	parser(t_list **param_list, char **argv, char **input_file,
			   char **output_file)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (i == 1)
		{
			*input_file = argv[i];
			i++;
			continue ;
		}
		if (argv[i + 1] == NULL)
		{
			*output_file = argv[i];
			break ;
		}
		ft_lstadd_back(param_list,
			ft_lstnew(ft_split(argv[i], ' ')));
		i++;
	}
}
