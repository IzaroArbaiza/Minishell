/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auskola- <auskola-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:23:21 by auskola-          #+#    #+#             */
/*   Updated: 2024/02/01 15:03:45 by auskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_pipes2(t_mini_data *data)
{
	data->is_double_quote = 0;
	data->is_single_quote = 0;
	data->is_backslash = 0;
	data->i = 0;
	data->j = 0;
	data->temp_pipes = 0;
	data->pipe_len = 0;
}

void	parse_pipes(t_mini_data *d)
{
	parse_pipes2(d);
	while (d->input[d->i] != '\0')
	{
		parse_check_backslash(d, d->i);
		parse_check_quote(d, d->i);
		if (d->input[d->i] == '|' && !d->is_double_quote && \
!d->is_single_quote && !d->is_backslash)
		{
			if (d->pipe_len > 0)
			{
				d->pipe[d->temp_pipes].line = \
				ft_substr(d->input, d->i - d->pipe_len, d->pipe_len);
				d->pipe[d->temp_pipes].pipe_tipe = 0;
				d->temp_pipes++;
				d->j = d->i;
				d->pipe_len = 0;
			}
		}
		else
			d->pipe_len++;
		d->i++;
	}
	if (d->i > d->j && d->temp_pipes <= d->num_pipes)
		d->pipe[d->temp_pipes].line = ft_substr(d->input, \
		d->i - d->pipe_len, d->pipe_len);
}

//	printf("%d-\n", data->pipe[pipe].num_tokens);
//		printf("token %d, %s \n", i, data->pipe[pipe].tokens[i].token);
//						j++;
//				printf("tiene comillas\n");
//		printf("Counter: %d\n", counter);

void	clear_tokens(t_mini_data *data, int pipe, int i, int counter)
{
	size_t	j;

	data->is_backslash = 0;
	while (i < data->pipe[pipe].num_tokens)
	{
		j = 0;
		while (j < ft_strlen(data->pipe[pipe].tokens[i].token))
		{
			if (data->pipe[pipe].tokens[i].token[j] == '\'')
			{
				if (j > 0)
				{
					if (data->pipe[pipe].tokens[i].token[j - 1] == '\\')
						;
					else
						counter++;
				}
			}
			j++;
		}
		if (counter % 2 == 0)
			clear_quote(data, pipe, i, 0);
		counter = 0;
		i++;
	}
}

//	printf("-%d__%d\n", token, lenght);
//	printf("esto lo quito: %c \n", data->pipe[pipe].tokens[token].token[i]);
//	printf("-%c-\n", data->pipe[pipe].tokens[token].token[i]);
//	printf("Reasulta: %s\n",  data->pipe[pipe].tokens[token].token);

void	clear_quote(t_mini_data *data, int pipe, int token, int back_slash)
{
	data->i = 0;
	data->j = 0;
	while (data->i < (int )ft_strlen(data->pipe[pipe].tokens[token].token))
	{
		back_slash = 0;
		if (data->pipe[pipe].tokens[token].token[data->i] == '\\')
		{
			back_slash = 1;
			data->i++;
		}
		if (back_slash == 0 && \
		data->pipe[pipe].tokens[token].token[data->i] == '\'')
		{
			data->pipe[pipe].tokens[token].token[data->i - data->j] = \
			data->pipe[pipe].tokens[token].token[data->i + 1];
			data->j++;
			data->i++;
		}
		else
			data->pipe[pipe].tokens[token].token[data->i - data->j] = \
			data->pipe[pipe].tokens[token].token[data->i];
		back_slash = 0;
		data->i++;
	}
	data->pipe[pipe].tokens[token].token[data->i - data->j] = '\0';
}
