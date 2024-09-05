/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auskola- <auskola-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 09:26:58 by auskola-          #+#    #+#             */
/*   Updated: 2024/02/02 13:42:29 by auskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_env_num(t_mini_data *data, int env_number)
{
	if (env_number >= 0 && env_number < data->env_array_len)
	{
		printf("%s=%s\n", data->env_data_temp[env_number].key, \
		data->env_data_temp[env_number].value);
		return (1);
	}
	else
		printf("cant printf %d\n", env_number);
	return (0);
}
/*
char	*return_env_num(t_mini_data *data, int env_number)
{
	if (env_number >= 0 && env_number < data->env_array_len)
	{
		printf("%s=%s\n", data->env_data_temp[env_number].key, \
		data->env_data_temp[env_number].value);
		return (1);
	}
	else
		printf("cant printf %d\n", env_number);
	return (0);
}
*/

void	parse_envp2(t_mini_data *data, char **envp)
{
	int		i;
	char	*key;
	char	*value;

	data->env_array_len = 0;
	while (envp[data->env_array_len] != NULL)
		data->env_array_len++;
	data->env_data_temp = (t_env_data *)malloc((data->env_array_len) * \
	sizeof(t_env_data));
	if (data->env_data_temp == NULL)
	{
		perror("Error asignement memory env_data_temp");
		exit(1);
	}
	i = 0;
	while (i < data->env_array_len)
	{
		key = get_key(envp[i]);
		data->env_data_temp[i].key = key;
		value = get_value(envp[i]);
		data->env_data_temp[i].value = value;
		i++;
	}
}

/* char	*get_key(char *str)
{
	int		i;
	int		len;
	char	*key;

	len = ft_strlen(str);
	key = (char *)malloc(sizeof(char) * len + 1);
	i = 0;
	while (str[i] != '=' && str[i] != '\0')
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	return (key);
} */

char	*get_value(char *str)
{
	int		i;
	char	*value;
	int		len;
	int		j;

	len = ft_strlen(str);
	value = (char *)malloc(sizeof(char) * len + 1);
	i = 0;
	while (str[i] != '=')
	{
		i++;
	}
	i++;
	j = 0;
	while (str[i] != '\0')
	{
		value[j] = str[i];
		i++;
		j++;
	}
	value[j] = '\0';
	return (value);
}

/* void	set_env(t_mini_data *data)
{
	int	i;
	int	counter;

	i = 0;
	while (data->envp[i] != NULL)
	{
		counter++;
		i++;
	}
	i = 0;
	while (data->envp[i] != NULL)
	{
		data->env_data_temp[i].key = get_key(data->envp[i]);
		data->env_data_temp[i].value = get_value(data->envp[i]);
		i++;
	}
} */

void	print_export(t_mini_data *data, t_env_data *bubble)
{
	int	i;

	i = 0;
	while (i < data->env_array_len)
	{
		printf("declare -x %s\n", bubble[i].key);
		i++;
	}
	make_env_join(data);
	make_env_split(data);
}
