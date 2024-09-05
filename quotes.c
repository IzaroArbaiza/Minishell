/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auskola- <auskola-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 09:26:58 by auskola-          #+#    #+#             */
/*   Updated: 2023/12/15 09:27:31 by auskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_need_quote(char *token_string)
{
	int	len;

	len = strlen(token_string);
	if (token_string[0] == '"' && token_string[len - 1] == '"' && len > 0)
		token_string = remove_quote(token_string, len, 0);
	return (token_string);
}

char	*remove_quote(char *token_string, int len, int i)
{
	int		canchange;
	char	*new_token;

	canchange = 1;
	while (i < len)
	{
		if (token_string[i] == ' ')
			canchange = 0;
		i++;
	}
	if (canchange == 1)
	{
		new_token = malloc(sizeof(char) * (len - 2));
		i = 0;
		while (i < len)
		{
			new_token[i] = token_string[i + 1];
			i++;
		}
		new_token[i] = '\0';
		free(token_string);
		return (new_token);
	}
	return (token_string);
}
