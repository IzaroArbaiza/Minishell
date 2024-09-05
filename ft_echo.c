/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarbaiza <iarbaiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:07:54 by iarbaiza          #+#    #+#             */
/*   Updated: 2024/02/02 17:01:20 by iarbaiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	full_n(char *str)
{
	int	i;

	i = 2;
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	option_n(char	**args, int *n)
{
	int	i;

	i = 1;
	while (args[i] != NULL && ft_strncmp(args[i], "-n", 2) == 0)
	{
		if (full_n(args[i]) == 0)
			break ;
		*n = 1;
		i++;
	}
	return (i);
}

char	*arg_filter(char *arg)
{
	int		i;
	int		j;
	int		len;
	char	*buffer;
	char	*res;

	i = 0;
	j = 0;
	len = ft_strlen(arg);
	buffer = (char *)malloc((len - 2) + 1);
	res = NULL;
	if (!buffer)
		return (NULL);
	else if ((arg[0] == '\'' && arg[len - 1] == '\'')
		|| (arg[0] == '\"' && arg[len - 1] == '\"'))
	{
		while (i++ < (len - 2))
			buffer[j++] = arg[i];
		buffer[len - 2] = '\0';
		res = buffer;
	}
	return (res);
}

/* 	if (strcmp("$?", args[1]) == 0)
		return (printf("%d\n", data->exit_number), 0); 
	// cambios
	// fin cambios
*/

int	ft_echo(char **args, t_mini_data *data)
{
	int		i;
	int		n;
	char	*res;

	n = 0;
	i = option_n(args, &n);
	if (args[1] && strcmp("$?", args[1]) == 0)
		return (printf("%d\n", data->exit_number), 0);
	else if (ft_echo2(args, data) == 1)
		return (0);
	while (args[i] != NULL)
	{
		res = arg_filter(args[i]);
		if (res != NULL)
			printf("%s", res);
		else
			printf("%s", args[i]);
		if (args[i][0] != '\0' && args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (n == 0)
		printf("\n");
	return (0);
}

int	ft_echo2(char **args, t_mini_data *data)
{
	int		env;

	if (args[1] && strncmp("\"", args[1], 1) == 0)
	{
		args[1] = ft_strtrim(args[1], "\"");
		if (strncmp("$", args[1], 1) == 0)
		{
			args[1] = ft_strtrim(args[1], "$");
			env = search_env(data, args[1]);
			if (env >= 0)
				printf("%s\n", get_env_by_id(data, env));
		}
		else
			return (printf("%s\n", args[1]), 1);
		return (1);
	}
	else if (args[1] && strncmp("$", args[1], 1) == 0)
	{
		args[1] = ft_strtrim(args[1], "$");
		env = search_env(data, args[1]);
		if (env >= 0)
			printf("%s\n", get_env_by_id(data, env));
		return (1);
	}
	return (0);
}

/* Hacer funcion para qruitar as primeras comillas */

/**
 * Ejemplos del comando echo:
 * 
 * 	$ echo "texto"
 * 	texto
 * 
 * 	$ echo $PWD
 * 	/User/Name/minishell
 * 
 * 	$ echo "estas en: $PWD"
 * 	estas en: /User/Name/minishell
 * 
 * 	$ echo "\n"
 * 	\n
 * 
*/