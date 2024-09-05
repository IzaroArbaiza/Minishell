/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarbaiza <iarbaiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:08:13 by iarbaiza          #+#    #+#             */
/*   Updated: 2024/01/30 16:08:24 by iarbaiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_repeated(char *args)
{
	int	i;
	int	j;
	int	h;

	i = 0;
	j = 0;
	h = 0;
	while (args[i])
	{
		if (args[i] == '"')
			j++;
		else if (args[i] == '\'')
			h++;
		i++;
	}
	if (j % 2 == 0 || h % 2 == 0)
		return (1);
	return (0);
}

char	*check_names(char *args)
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
		if (!is_repeated(args))
			return (NULL);
		if (args[i] >= 65 && args[i] <= 122)
			new[j++] = args[i++];
		else if (args[i] == 34 || args[i] == 39)
			i++;
		else
			return (NULL);
	}
	new[j] = '\0';
	return (new);
}

int	compar(char *args, const char *command)
{
	return (ft_strncmp(args, command, ft_strlen(args) + 1));
}

int	compar2(char *args, const char *command)
{
	int		res;
	char	*checked;

	checked = check_names(args);
	if (!checked)
		return (1);
	res = ft_strncmp(checked, command, ft_strlen(args) + 1);
	free(checked);
	return (res);
}
