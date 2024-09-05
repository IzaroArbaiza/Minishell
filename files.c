/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auskola- <auskola-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:09:00 by auskola-          #+#    #+#             */
/*   Updated: 2024/02/02 13:37:29 by auskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_path(t_mini_data *data, char *arg)
{
	int		i;
	char	*paths[3];

	i = 0;
	if (access(arg, X_OK) == 0)
		return (data->exec_path = arg, 1);
	parse_path(data);
	while (i < data->num_paths)
	{
		if (access(data->paths[i], X_OK) == 0)
		{
			paths[0] = ft_strdup(data->paths[i]);
			paths[1] = ft_strjoin(paths[0], "/");
			paths[2] = ft_strjoin(paths[1], arg);
			free (paths[0]);
			free (paths[1]);
			if (access(paths[2], X_OK) == 0)
				return (data->exec_path = paths[2], 1);
			free (paths[2]);
		}
		i++;
	}
	return (0);
}

/* 
	char *d;
	d = get_env_by_id(data, search_env(data, "PATH"));
	printf("aa-%s--", d);
	
	if (data->path == NULL)
	{
		perror("Error: Path not found");
		exit(EXIT_FAILURE);
		return ;
	} */
void	parse_path(t_mini_data *data)
{
	char	*temp;

	if (search_env(data, "PATH") == -1)
	{
		data->num_paths = 0;
		return ;
	}
	temp = merge_env_data(data, search_env(data, "PATH"));
	data->path = get_value(temp);
	free(temp);
	data->num_paths = ft_count_strings(data->path, ':');
	data->paths = ft_split(data->path, ':');
}
