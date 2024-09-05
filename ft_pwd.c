/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auskola- <auskola-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 09:22:50 by iarbaiza          #+#    #+#             */
/*   Updated: 2024/01/04 15:46:28 by auskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	len_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

void	free_cmd(char **cmd)
{
	int	i;

	i = len_cmd(cmd);
	while (i >= 0)
	{
		free(cmd[i]);
		i--;
	}
	free(cmd);
}

//	free_cmd(cmd);
int	ft_pwd(char **cmd)
{
	char	*pwd;

	(void)cmd;
	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
