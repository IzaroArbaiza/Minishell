/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auskola- <auskola-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:46:06 by auskola-          #+#    #+#             */
/*   Updated: 2024/02/02 13:44:07 by auskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* char	*merge_env_data(t_mini_data	*data, int i)
{
	char	*temp2;
	char	*temp3;

	temp2 = ft_strjoin(data->env_data_temp[i].key, "=");
	temp3 = ft_strjoin(temp2, data->env_data_temp[i].value);
	free(temp2);
	return (temp3);
} */

char	*get_env_by_id(t_mini_data *data, int pos)
{
	if (pos >= 0 && pos < data->env_array_len)
		return (data->env_data_temp[pos].value);
	else
		return (NULL);
}

char	*merge_env_data(t_mini_data	*data, int i)
{
	char	*temp2;
	char	*temp3;

	temp2 = ft_strjoin(data->env_data_temp[i].key, "=");
	temp3 = ft_strjoin(temp2, data->env_data_temp[i].value);
	free(temp2);
	return (temp3);
}

void	free_env_(t_mini_data *data)
{
	data->i = 0;
	data->j = 0;
	while (data->i < data->env_array_len)
	{
		free(data->env_data_temp[data->i].key);
		data->env_data_temp[data->i].key = NULL;
		free(data->env_data_temp[data->i].value);
		data->env_data_temp[data->i].value = NULL;
		data->i++;
	}
	free(data->env_data_temp);
	data->env_data_temp = NULL;
}
