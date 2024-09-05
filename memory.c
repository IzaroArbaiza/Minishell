/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auskola- <auskola-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:28:44 by auskola-          #+#    #+#             */
/*   Updated: 2024/02/01 14:23:13 by auskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	line_free(t_mini_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i <= data->num_pipes)
	{
		j = 0;
//		printf("lo que %d, %d, %d\n", i,j,  data->pipe[i].num_tokens) ;
		while (j < data->pipe[i].num_tokens)
		{
			free(data->pipe[i].tokens[j].token);
			j++;
		}
		free (data->pipe[i].tokens);
		free (data->pipe[i].line);
		i++;
	}
//aa	free(data->pipe);
} */

void	token_free(t_mini_data *data, int i)
{
	int	j;

	j = 0;
	while (j < data->pipe[i].num_tokens)
	{
		free(data->pipe[i].tokens[j].token);
		j++;
	}
	free (data->pipe[i].tokens);
	free (data->pipe[i].line);
	i++;
	free_pipes(data);
}

void	free_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	malloc_pipes(t_mini_data *data)
{
	int	i;

	i = 0;
	data->pipes = malloc(sizeof(int *) * (data->num_pipes + 1));
	data->fd = malloc(sizeof(int *) * (data->num_pipes + 1));
	while (i <= data->num_pipes)
	{
		data->pipes[i] = malloc(sizeof(int) * 2);
		i++;
	}
}

void	free_pipes(t_mini_data *data)
{
	int	i;

	i = 0;
	while (i <= data->num_pipes)
	{
		free(data->pipes[i]);
		i++;
	}
	free(data->pipes);
	free(data->fd);
	data->num_pipes = 0;
}
