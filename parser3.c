/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auskola- <auskola-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:36:11 by auskola-          #+#    #+#             */
/*   Updated: 2024/01/04 16:38:47 by auskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_check_quote(t_mini_data *data, int i)
{
	if (data->input[i] == '"' && !data->is_single_quote && !data->is_backslash)
		data->is_double_quote = change_quote(data->is_double_quote);
	if (data->input[i] == '\'' && !data->is_double_quote && !data->is_backslash)
		data->is_single_quote = change_quote(data->is_single_quote);
}

void	parse_check_backslash(t_mini_data *data, int i)
{
	if (data->input[i] == '\\')
	{
		data->is_backslash = 1;
		i++;
	}
	else
		data->is_backslash = 0;
	data->is_backslash = 0;
}

void	parse_tokens_backslash(t_mini_data *d, int pipe)
{
	if (d->pipe[pipe].line[d->i] == '\\')
	{
		d->is_backslash = 1;
		d->i++;
	}
	else
		d->is_backslash = 0;
}

void	parse_tokens2(t_mini_data *d)
{
	d->is_double_quote = 0;
	d->is_single_quote = 0;
	d->is_backslash = 0;
	d->i = 0;
	d->j = 0;
}

void	num_pipes(t_mini_data *data)
{
	clear_pipes(data);
	while (data->input[data->i] != '\0')
	{
		if (data->input[data->i] == '\\')
		{
			data->is_backslash = 1;
			data->i++;
		}
		else
			data->is_backslash = 0;
		if (data->input[data->i] == '"' && \
		!data->is_single_quote && !data->is_backslash)
			data->is_double_quote = change_quote(data->is_double_quote);
		if (data->input[data->i] == '\'' && \
		!data->is_double_quote && !data->is_backslash)
			data->is_single_quote = change_quote(data->is_single_quote);
		if (data->input[data->i] == '|' && !data->is_double_quote && \
		!data->is_single_quote && !data->is_backslash)
			data->num_pipes++;
		data->i++;
	}
	data->pipe = malloc(sizeof(t_pipe) * (data->num_pipes + 1));
}
