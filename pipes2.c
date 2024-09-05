/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auskola- <auskola-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:50:44 by auskola-          #+#    #+#             */
/*   Updated: 2024/02/01 14:52:11 by auskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(t_mini_data *data, int current_process)
{
	int	i;

	i = 0;
	while (i < data->num_pipes)
	{
		if (current_process != i)
			close(data->pipes[i][0]);
		if (current_process != i + 1)
			close(data->pipes[i][1]);
		i++;
	}
}

void	parse_line(t_mini_data *data)
{
	int	i;

	num_pipes(data);
	parse_pipes(data);
	i = 0;
	if (data->debug)
		debug_pipes(data);
	while (i <= data->num_pipes)
	{
		num_tokens(data, i);
		parse_tokens(data, i);
		clear_tokens(data, i, 0, 0);
		if (data->debug)
			debug_tokens(data, i);
		i++;
	}
	parse_command(data);
}

void	clear_pipes(t_mini_data *data)
{
	data->is_double_quote = 0;
	data->is_single_quote = 0;
	data->is_backslash = 0;
	data->num_pipes = 0;
	data->i = 0;
}
