/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auskola- <auskola-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:02:47 by auskola-          #+#    #+#             */
/*   Updated: 2024/02/02 16:43:00 by auskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_names(char	*args)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = (char *)malloc(ft_strlen(args) + 1);
	if (!args || !new)
		return (NULL);
	while (args[i])
	{
		if (args[i] >= 65 && args[i] <= 122)
		{
			new[j] = args[i];
			i++;
			j++;
		}
		else if (args[i] == 34)
			i++;
		else
			return (NULL);
	}
	new[j] = '\0';
	return (new);
}
/* else if (strncmp(data->pipe[pipe].tokens[0].token, "$?", 2) == 0)
	return (1); */

int	is_builtin(t_mini_data *data, int pipe)
{
	if (data->pipe[pipe].num_tokens == 0)
		return (0);
	if (strncmp(data->pipe[pipe].tokens[0].token, "env", 3) == 0)
		return (1);
	else if (strncmp(data->pipe[pipe].tokens[0].token, "unset", 5) == 0)
		return (1);
	else if (strncmp(data->pipe[pipe].tokens[0].token, "r", 1) == 0)
		return (1);
	else if (strncmp(data->pipe[pipe].tokens[0].token, "export", 6) == 0)
		return (1);
	else if (strncmp(data->pipe[pipe].tokens[0].token, "exit", 4) == 0)
		return (1);
	else if (strncmp(data->pipe[pipe].tokens[0].token, "<<", 2) == 0)
		return (1);
	return (0);
}
/* 	else if (strncmp(args[0], "$?", 2) == 0)    
		return (printf("%d\n", data->exit_number), 1); */
/* 	else if (strncmp(args[0], "\'", 2) == 0)
		return (printf("caracter invalido"), 1); */
		//			return (env_show(data), 1);

int	execute_builtin(t_mini_data *data, char **args, int pipe)
{
	char	**keys;

	if (!args)
		return (0);
	else if (strncmp(args[0], "pwd", (ft_strlen(args[0]) + 1)) == 0)
		return (ft_pwd(args), 1);
	else if (execute_builtin2(data, args, pipe))
		return (1);
	else if (strncmp(args[0], "export", (ft_strlen(args[0]) + 1)) == 0)
	{
		if (!args[1])
			return (bubble_sort(data, 0), 1);
		else
		{
			keys = ft_split(args[1], '=');
			if (keys[1] == NULL)
				return (1);
			env_export(data, keys[0], keys[1]);
			return (free(keys), 1);
		}
	}
	else if (strncmp(args[0], "cd", (ft_strlen(args[0]) + 1)) == 0)
		return (1);
	return (0);
}

int	execute_builtin2(t_mini_data *data, char **args, int pipe)
{
	(void) pipe;
	if (strncmp(args[0], "cd", (ft_strlen(args[0]) + 1)) == 0)
		return (ft_cd(args), 1);
	else if (strncmp(args[0], "echo", (ft_strlen(args[0]) + 1)) == 0)
		return (ft_echo(args, data), 1);
	else if (strncmp(args[0], "env", (ft_strlen(args[0]) + 1)) == 0)
		return (env_show(data), 1);
	else if (strncmp(args[0], "unset", (ft_strlen(args[0]) + 1)) == 0)
		return (unset_env(data, args[1]), 1);
	else if (strncmp(args[0], "r", (ft_strlen(args[0]) + 1)) == 0)
		return (make_env_join(data), make_env_split(data), 1);
	else if (strncmp(args[0], "exit", 4) == 0)
		return (1);
	else if (strncmp(args[0], "<<", 2) == 0)
		return (printf("Heredoc no implementado\n"), 1);
	else
		return (0);
}
/**
 * Los siguientes comandos, al ser ejecutados con un "|", no se ejecutan:
 * 	- cd
 * 	- exit
 * 	- export
 * 	- unset
 * 
*/
