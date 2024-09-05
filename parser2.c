/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auskola- <auskola-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:23:21 by auskola-          #+#    #+#             */
/*   Updated: 2024/01/26 16:25:22 by auskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	reduce_parse_tokens_4(t_mini_data *data, int pipe)
{
	if (data->pipe[pipe].line[data->i] == '>' && !data->is_double_quote && \
	!data->is_single_quote && !data->is_double_quote && !data->is_backslash)
	{
		if (data->token_len == 0)
		{
			if (data->pipe[pipe].line[data->i + 1] == '>')
			{
				data->pipe[pipe].tokens[data->tokens].token = ft_strdup(">>");
				data->i++;
			}
			else
				data->pipe[pipe].tokens[data->tokens].token = ft_strdup(">");
		}
		data->tokens++;
		data->j = data->i;
		return (1);
	}
	return (0);
}

int	reduce_parse_tokens_3(t_mini_data *data, int pipe)
{
	if (data->pipe[pipe].line[data->i] == '<' && !data->is_double_quote && \
		!data->is_single_quote && !data->is_double_quote && !data->is_backslash)
	{
		if (data->token_len == 0)
		{
			if (data->pipe[pipe].line[data->i + 1] == '<')
			{
				data->pipe[pipe].tokens[data->tokens].token = ft_strdup("<<");
				data->i++;
			}
			else
				data->pipe[pipe].tokens[data->tokens].token = ft_strdup("<");
		}
		data->tokens++;
		data->j = data->i;
		return (1);
	}
	return (0);
}

int	reduce_parse_tokens_2(t_mini_data *data, int pipe)
{
	if (data->pipe[pipe].line[data->i] == ' ' && !data->is_single_quote \
	&& !data->is_double_quote && !data->is_backslash)
	{
		if (data->token_len > 0)
		{
			data->pipe[pipe].tokens[data->tokens].token = \
			ft_substr(data->pipe[pipe].line, data->i - \
			data->token_len, data->token_len);
			data->tokens++;
			data->j = data->i;
			data->token_len = 0;
		}
		return (1);
	}
	return (0);
}

int	reduce_parse_tokens_1(t_mini_data *data, int pipe)
{
	if (data->pipe[pipe].line[data->i] == '\\')
	{
		data->is_backslash = 1;
		data->i++;
	}
	else
		data->is_backslash = 0;
	if (data->pipe[pipe].line[data->i] == '"' \
	&& !data->is_single_quote && !data->is_backslash)
	{
		data->token_len++;
		data->is_double_quote = change_quote(data->is_double_quote);
		return (1);
	}
	else if (data->pipe[pipe].line[data->i] == '\'' \
	&& !data->is_double_quote && !data->is_backslash)
	{
		data->is_single_quote = change_quote(data->is_single_quote);
		data->token_len++;
		return (1);
	}
	return (0);
}

void	initialize_parse_tokens(t_mini_data *data, int pipe)
{
	data->is_double_quote = 0;
	data->is_single_quote = 0;
	data->is_backslash = 0;
	data->i = 0;
	data->j = 0;
	data->tokens = 0;
	data->token_len = 0;
	if (data->pipe[pipe].line[data->i] == ' ')
		data->i++;
}
