/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auskola- <auskola-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 09:26:58 by auskola-          #+#    #+#             */
/*   Updated: 2024/02/02 16:47:25 by auskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(char *str)
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
}

int	search_env(t_mini_data *data, char *key)
{
	int	i;

	i = 0;
	while (i < data->env_array_len)
	{
		if (data->env_data_temp[i].key != NULL)
		{
			if (strcmp(data->env_data_temp[i].key, key) == 0)
				return (i);
		}
		i++;
	}
	return (-1);
}

void	make_env_split(t_mini_data *data)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	data->env_data_temp = (t_env_data *)malloc((data->env_array_len + \
	data->add_export) * sizeof(t_env_data));
	if (data->env_data_temp == NULL)
	{
		perror("Error asignement memory env_data_temp");
		exit(1);
	}
	while (i < data->env_array_len)
	{
		key = get_key(data->envp[i]);
		data->env_data_temp[i].key = key;
		value = get_value(data->envp[i]);
		data->env_data_temp[i].value = value;
		free(data->envp[i]);
		i++;
	}
	free(data->envp);
}

	/*          
	temp2 = ft_strjoin(data->env_data_temp[data->i].key, "=");
	temp3 = ft_strjoin(temp2, data->env_data_temp[data->i].value);
	free(temp2);
	data->envp[data->j] = temp3; 
	*/

void	make_env_join(t_mini_data *data)
{
	data->i = 0;
	data->j = 0;
	data->envp = (char **)malloc((data->env_array_len + \
	1) * sizeof(char *) + 1);
	if (data->envp == NULL)
	{
		perror("Error asignement memory envp");
		exit(1);
	}
	while (data->i < data->env_array_len)
	{
		if (data->env_data_temp[data->i].key && \
		data->env_data_temp[data->i].value)
			join_env_data(data, data->i);
		data->i++;
	}
	if (data->add_unset)
	{
		data->envp[data->add_unset] = NULL;
		free(data->envp[data->add_unset]);
	}
	data->envp[data->i] = NULL;
	free(data->envp[data->i]);
	free(data->env_data_temp);
}

void	join_env_data(t_mini_data	*data, int i)
{
	char	*temp2;
	char	*temp3;

	temp2 = ft_strjoin(data->env_data_temp[i].key, "=");
	temp3 = ft_strjoin(temp2, data->env_data_temp[i].value);
	free(temp2);
	data->envp[i] = temp3;
	free(data->env_data_temp[data->i].key);
	free(data->env_data_temp[data->i].value);
}

/* void	parse_envp(t_mini_data *data)
{

	int     i;
	int 	env;
	char	**temp;
	char	*str;
    char    *key;
    char    *value;
    char   *temp2;

 	i = 0;
    while (data->envp[i] != NULL)
    {
        i++;
    } 
    data->env_array_len = i;
    data->env_data_temp = (t_env_data *)\
	malloc((data->env_array_len + 1) * sizeof(t_env_data));
    if (data->env_data_temp == NULL)
    {
        perror("Error asignement memory env_data_temp");
        exit(1);
    }
    i = 0;

	while (i < data->env_array_len)
	{
		printf("envp[%d]: %s\n", i, data->envp[i]);
		i++;
	}
    exit (0);
	while (data->envp[i] != NULL)
	{
        key = get_key(data->envp[i]);
        data->env_data_temp[i].key = key;
        value = get_value(data->envp[i]);
        data->env_data_temp[i].value = value;
        free(data->envp[i]);
        i++;
	}

    i = 0;
    data->env_data = data->env_data_temp;
	while (i < data->env_array_len)
	{
		printf("Key: %s\n", data->env_data_temp[i].key);
		printf("     %s\n", data->env_data_temp[i].value);
        temp2 = ft_strjoin(data->env_data_temp[i].key, "=");
        data->envp[i] = ft_strjoin(temp2, data->env_data_temp[i].value);
        free(data->env_data_temp[i].key);
        free(data->env_data_temp[i].value);  
		i++;
	}
    free(data->env_data_temp);
} */
