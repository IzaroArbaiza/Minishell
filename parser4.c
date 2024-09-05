/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auskola- <auskola-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:50:05 by auskola-          #+#    #+#             */
/*   Updated: 2024/02/01 14:36:35 by auskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_tokens(t_mini_data *data, int pipe)
{
	initialize_parse_tokens(data, pipe);
	while (data->pipe[pipe].line[data->i] != '\0')
	{
		if (reduce_parse_tokens_1(data, pipe))
			;
		else if (reduce_parse_tokens_2(data, pipe))
			;
		else if (reduce_parse_tokens_3(data, pipe))
			;
		else if (reduce_parse_tokens_4(data, pipe))
			;
		else
			data->token_len++;
		data->i++;
	}
	if (data->i > data->j && data->tokens < data->pipe[pipe].num_tokens)
	{
		data->pipe[pipe].tokens[data->tokens].token = \
		ft_substr(data->pipe[pipe].line, data->i - \
		data->token_len, data->token_len);
		data->tokens++;
	}
}
//				printf("Resultado PID:%d\n", data->wait_pid);

void	reduce_parse_command1(t_mini_data *data)
{
	malloc_pipes(data);
	if (data->num_pipes == 0)
	{
		if (is_builtin(data, 0))
			execute_command(data, 0);
		else
		{
			data->pid = fork();
			if (data->pid == -1)
				exit(EXIT_FAILURE);
			if (data->pid == 0)
			{
				execute_command(data, 0);
				exit(EXIT_SUCCESS);
			}
			else
			{
				data->wait_pid = waitpid(data->pid, &data->exit_number, 0);
				data->exit_number = WEXITSTATUS(data->exit_number);
				data->wait_pid = data ->exit_number;
				wait(NULL);
			}
		}
	}
}

void	reduce_parse_command2(t_mini_data *data)
{
	data->stdout_copy = dup(STDOUT_FILENO);
	if (data->i == 0)
	{
		dup2(data->pipes[data->i][1], STDOUT_FILENO);
		close(data->pipes[data->i][1]);
	}
	else if (data->i < data->num_pipes)
	{
		dup2(data->pipes[data->i -1][0], STDIN_FILENO);
		dup2(data->pipes[data->i][1], STDOUT_FILENO);
		close(data->pipes[data->i - 1][0]);
		close(data->pipes[data->i][1]);
	}
	else
	{
		dup2(data->pipes[data->i -1][0], STDIN_FILENO);
		close(data->pipes[data->i - 1][0]);
	}
}

void	reduce_parse_command_wait(t_mini_data *data)
{
	close_pipes(data, -1);
	data->j = 0;
	while (data->j <= data->num_pipes)
	{
		wait(NULL);
		if (data->pipe[data->j].num_tokens == 0)
			break ;
		if (strncmp(data->pipe[data->j].tokens[0].token, "exit", 4) == 0)
			data->exit_now = 1;
		data->j++;
	}
}

void	reduce_parse_command_fd(t_mini_data *data)
{
	reduce_parse_command2(data);
	execute_command(data, data->i);
	close(data->stdout_copy);
	exit(EXIT_SUCCESS);
}
