/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auskola- <auskola-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:06:08 by auskola-          #+#    #+#             */
/*   Updated: 2024/02/02 12:38:37 by auskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
char	*trim_path(char *path);
char	*get_env(char *var_name, char **env);
int		cd_too_many(char **args);
int		cd_point_point(void);
int		ft_cd(char **args, char **env);
*/

char	*trim_path(char *path)
{
	int	i;
	int	len;

	len = ft_strlen(path);
	if (len > 0 && path[len - 1] == '/')
		len --;
	i = len - 1;
	while (i >= 0)
	{
		if (path[i] == '/')
		{
			if (i == 0)
				path[i + 1] = 0;
			else
				path[i] = 0;
			break ;
		}
		i--;
	}
	return (path);
}

int	cd_too_many(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
		if (i >= 2)
			return (1);
	return (0);
}

int	cd_point_point(void)
{
	char	*var;

	var = trim_path(getcwd(NULL, 0));
	if (!var)
	{
		printf("allocation error using getcw for cd\n");
		return (0);
	}
	if (chdir(var))
	{
		free(var);
		printf ("Error\n");
		return (0);
	}
	free(var);
	return (1);
}

int	ft_cd(char **args)
// int	ft_cd(char **args, char **env)
{
	if (cd_too_many(args))
	{
		printf("minishell IA :) cd: too many arguments\n");
		return (1);
	}
	else if (!strncmp(args[1], "..", 2))
	{
		if (cd_point_point())
			return (0);
	}
	else if (chdir(args[1]))
	{
		printf("minishell IA :) cd: %s: No such file or directory\n", args[1]);
		return (1);
	}
	return (0);
}
