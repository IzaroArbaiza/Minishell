/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auskola- <auskola-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:23:21 by auskola-          #+#    #+#             */
/*   Updated: 2024/02/01 14:35:36 by auskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	parse_line_old(t_mini_data *data)
{
	int	i;

	num_pipes(data);
	parse_pipes(data);
	i = 0;
	
	while (i <= data->num_pipes)
	{
		num_tokens(data, i);
		parse_tokens(data, i);
		i++;
	}
	parse_command(data);
} */

int	change_quote(int value)
{
	if (value == 0)
		return (1);
	else
		return (0);
}
//d->token_len = 0;

int	reduce_line_numtokens2(t_mini_data *d, int pipe)
{
	if (d->pipe[pipe].line[d->i] == '<' && !d->is_double_quote \
	&& !d->is_single_quote && !d->is_backslash)
	{
		d->tokens++;
		if (d->pipe[pipe].line[d->i + 1] == '<' && !d->is_double_quote \
		&& !d->is_single_quote && !d->is_backslash)
			d->i++;
		return (1);
	}
	else if (d->pipe[pipe].line[d->i] == '>' && !d->is_double_quote \
	&& !d->is_single_quote && !d->is_backslash)
	{
		d->tokens++;
		if (d->pipe[pipe].line[d->i + 1] == '>' && !d->is_double_quote \
		&& !d->is_single_quote && !d->is_backslash)
			d->i++;
		d->token_len = 0;
		return (1);
	}
	return (0);
}

int	reduce_line_numtokens1(t_mini_data *d, int pipe)
{
	if (d->pipe[pipe].line[d->i] == '"' \
	&& !d->is_single_quote && !d->is_backslash)
	{
		d->is_double_quote = change_quote(d->is_double_quote);
		return (1);
	}
	else if (d->pipe[pipe].line[d->i] == '\'' \
	&& !d->is_double_quote && !d->is_backslash)
	{
		d->is_single_quote = change_quote(d->is_single_quote);
		return (1);
	}
	else if (d->pipe[pipe].line[d->i] == ' ' \
	&& !d->is_double_quote && !d->is_single_quote && !d->is_backslash)
	{
		if (d->token_len > 0)
		{
			d->tokens++;
			d->token_len = 0;
		}
		return (1);
	}
	return (0);
}

void	num_tokens(t_mini_data *d, int pipe)
{
	parse_tokens2(d);
	d->tokens = 0;
	d->token_len = 0;
	while (d->pipe[pipe].line[d->i] != '\0')
	{
		parse_tokens_backslash(d, pipe);
		if (reduce_line_numtokens1(d, pipe))
			;
		else if (reduce_line_numtokens2(d, pipe))
			;
		else
			d->token_len++;
		d->i++;
	}
	if (d->token_len > 0)
		d->tokens++;
	d->pipe[pipe].num_tokens = d->tokens;
	d->pipe[pipe].tokens = malloc(sizeof(t_token) * (d->tokens + 1));
}

//	int	stdout_copy;

void	parse_command(t_mini_data *data)
{
	reduce_parse_command1(data);
	if (data->num_pipes > 0)
	{
		data->i = 0;
		while (data->i <= data->num_pipes)
		{
			if (pipe(data->pipes[data->i]) == -1)
				exit(EXIT_FAILURE);
			data->fd[data->i] = fork();
			if (data->fd[data->i] == -1)
				exit(EXIT_FAILURE);
			if (data->fd[data->i] == 0)
			{
				reduce_parse_command_fd(data);
			}
			else
			{
				if (data->i > 0)
					close(data->pipes[data->i - 1][0]);
				close(data->pipes[data->i][1]);
				data->i++;
			}
		}
		reduce_parse_command_wait(data);
	}
}
/* 			data->pid = fork();
			if (data->pid == -1) {
				perror("fork");
				exit(EXIT_FAILURE);
			}
			if (data->pid == 0) { // Proceso hijo
				dup2(data->pipes[1][1], STDIN_FILENO);
				close_pipes(data);
				execute_command(data, 1);
				exit(EXIT_SUCCESS);
			} 
			wait(NULL); // Espera a que el hijo termine
     while (i <= data->num_pipes)
    {
		if (pipe(data->pipes[i]) == -1) 
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}

		data->pid =fork();
		if(data->pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}



		is_built_command = 0;

		printf("FIN");
	
		if (is_built_command)
			execute_builtin(data->pipe[i].line);
		else
		{
			execute_command(data, i);

		}	

		i++;
		
	
	}
	*/
