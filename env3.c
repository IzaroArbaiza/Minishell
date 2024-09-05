/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auskola- <auskola-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:21:46 by auskola-          #+#    #+#             */
/*   Updated: 2024/02/02 16:21:19 by auskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_show(t_mini_data *data)
{
	int	i;

	i = 0;
	while (i < data->env_array_len)
	{
		if (data->env_data_temp[i].key != NULL)
			printf("%s=%s\n", data->env_data_temp[i].key, \
			data->env_data_temp[i].value);
		i++;
	}
}

void	env_export(t_mini_data *data, char *key, char *value)
{
	int	i;

	i = search_env(data, key);
	if (i == -1)
	{
		data->add_export = 1;
		make_env_join(data);
		make_env_split(data);
		data->env_data_temp[data->env_array_len].key = key;
		data->env_data_temp[data->env_array_len].value = value;
		data->add_export = 0;
		data->env_array_len++;
		make_env_join(data);
		make_env_split(data);
	}
	else
	{
		if (strcmp(data->env_data_temp[i].key, key) == 0)
		{
			printf("%d\n", i);
			free (data->env_data_temp[i].value);
			data->env_data_temp[i].value = value;
			free(key);
		}
	}
}

int	unset_env(t_mini_data *d, char *key)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (i < d->env_array_len)
	{
		if (!found && strcmp(d->env_data_temp[i].key, key) == 0)
		{
			free(d->env_data_temp[i].key);
			free(d->env_data_temp[i].value);
			d->env_data_temp[i].key = NULL;
			d->env_data_temp[i].value = NULL;
			found = 1;
		}
		if (found && i < d->env_array_len - 1)
		{
			d->env_data_temp[i].key = d->env_data_temp[i + 1].key;
			d->env_data_temp[i].value = d->env_data_temp[i + 1].value;
		}
		i++;
	}
	if (found)
		d->env_array_len--;
	return (env_show(d), found);
}

void	bubble_sort(t_mini_data *d, int swapped)
{
	t_env_data	*temporal;
	t_env_data	temp;

	temporal = d->env_data_temp;
	d->i = 0;
	while (d->i < d->env_array_len)
	{
		d->j = 0;
		while (d->j < d->env_array_len - 1)
		{
			if (strncmp(temporal[d->j].key, temporal[d->j + 1].key, \
			ft_strlen(temporal[d->j].key)) > 0)
			{
				temp.key = temporal[d->j].key;
				temporal[d->j].key = temporal[d->j + 1].key;
				temporal[d->j + 1].key = temp.key;
				swapped = 1;
			}
			d->j++;
		}
		d->i++;
		if (swapped == 0)
			break ;
	}
	print_export (d, temporal);
}
