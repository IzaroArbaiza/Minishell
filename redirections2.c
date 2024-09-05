/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarbaiza <iarbaiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:47:02 by auskola-          #+#    #+#             */
/*   Updated: 2024/02/02 17:03:28 by iarbaiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirect( char **argv, int i)
{
	if (strncmp(argv[i], "<<", 2) == 0)
		return (HERE_DOCUMENT);
	else if (strncmp(argv[i], "<", 1) == 0)
		return (DATA_INPUT);
	else if (strncmp(argv[i], ">", 1) == 0)
		return (WRITE);
	else if (strncmp(argv[i], ">>", 2) == 0)
		return (APPEND);
	else
		return (0);
}

void	close_redirection(t_mini_data *data)
{
	if (data->file_id >= 0)
	{
		close(data->file_id);
		data->file_id = -1;
	}
}
/* 	if (data->pipe[line_number].tokens[i].token[0] == '"')
		return (ft_strdup_trim(data->pipe[line_number].tokens[i].token));

	printf("tokena: %s\n", data->pipe[line_number].tokens[i].token);
	if (strncmp(data->pipe[line_number].tokens[i].token, "\'", 1) == 0)
		return (printf("casi\n"), \
		ft_strdup_trim(data->pipe[line_number].tokens[i].token));
	else if (strncmp(data->pipe[line_number].tokens[i].token, "\"", 1) == 0)
		return ("\""); 
	else if (strncmp(data->pipe[line_number].tokens[i].token, "\'" , 2) == 0)
		return (ft_strdup_trim(data->pipe[line_number].tokens[i].token));
	else
	*/
	// if (strncmp(data->pipe[line_number].tokens[i].token, "\'", 1) == 0)
	// 	return (ft_strdup_trim(data->pipe[line_number].tokens[i].token));

char	*clean_text(t_mini_data *data, int line_number, int i)
{
	if (data->pipe[line_number].tokens[i].token[0] == '"')
		return (ft_strdup_trim(data->pipe[line_number].tokens[i].token));
	if (strncmp(data->pipe[line_number].tokens[i].token, "\"", 1) == 0)
		return ("\"");
	else if (strncmp(data->pipe[line_number].tokens[i].token, "\'", 2) == 0)
		return (ft_strdup_trim(data->pipe[line_number].tokens[i].token));
	else
		return (ft_strdup(data->pipe[line_number].tokens[i].token));
}

void	update_redirections(t_mini_data *data, int pipe, \
int i, int data_type)
{
	data->pipe[pipe].num_redirections++;
	data->pipe[pipe].tokens[i].redirection = data_type;
	data->pipe[pipe].tokens[i + 1].redirection = FILE_NAME;
}

void	open_redirection(t_mini_data *data, int redirection)
{
	if (redirection == WRITE)
		data->out = open(data->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redirection == APPEND)
		data->out = open(data->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redirection == WRITE || redirection == APPEND)
	{
		if (data->out < 0)
		{
			perror("Error open file ");
			exit(EXIT_FAILURE);
		}
		dup2(data->out, STDOUT_FILENO);
		close(data->out);
	}
	if (redirection == DATA_INPUT)
	{
		if (data->in < 0)
		{
			perror("Error opening file Heredoc");
			exit(EXIT_FAILURE);
		}
		dup2(data->in, STDIN_FILENO);
		close(data->in);
	}
}
