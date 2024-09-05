/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auskola- <auskola-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:23:21 by auskola-          #+#    #+#             */
/*   Updated: 2023/12/15 11:46:43 by auskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_pipes(t_mini_data *data)
{
	int	i;

	printf("num_pipes: %d\n", data->num_pipes);
	i = 0;
	while (i <= data->num_pipes)
	{
		printf("pipe %d: %s\n", i, data->pipe[i].line);
		i++;
	}
}

void	debug_tokens(t_mini_data *data, int pipe)
{
	int	i;

	printf("num_tokens: %d\n", data->pipe[pipe].num_tokens);
	i = 0;
	while (i < data->pipe[pipe].num_tokens)
	{
		printf("token %d: %s\n", i, data->pipe[pipe].tokens[i].token);
		i++;
	}
}

/* 	while (i < d->env_array_len)
	{
		printf("envp[%d]: %s\n", i, d->envp[i]);
		i++;
	} */
/* 
	d->env_array_len = i;
	d->env_array = (char **)malloc((d->env_array_len + 1) * sizeof(char *)); */
/*  	
	i = 0;
	while (d->envp[i] != NULL)
	{
		d->env_array[i] = ft_strdup(d->envp[i]);
		
		printf("envp-[%d]-: %s\n", i, d->env_array[i]);
		i++;
	}   
 */

void	debug_envp_data(t_mini_data *d)
{
	int	i;

	i = 0;
	while (d->env_data_temp[i].key != NULL)
	{
		printf("envp_data[%d].key: %s\n", i, d->env_data_temp[i].key);
		printf("envp_data[%d].value: %s\n", i, d->env_data_temp[i].value);
		i++;
	}
}
