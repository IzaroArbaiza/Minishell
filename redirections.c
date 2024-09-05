/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auskola- <auskola-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:47:02 by auskola-          #+#    #+#             */
/*   Updated: 2024/02/02 16:47:15 by auskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 			d->stdout_copy = dup(STDOUT_FILENO);
			d->out = open(d->tempfilename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			while (1)
			{
				heredoc_text = readline(">");
				if (!heredoc_text)
				{
					free(heredoc_text);
					break ;
				}
				h_d = dup2(d->out, STDOUT_FILENO);
				if (strcmp(heredoc_text, \
				d->pipe[pipe].tokens[i + 1].token) == 0)
				{
					free(heredoc_text);
					dup2(d->stdout_copy, STDOUT_FILENO);
					close(d->out);
					break ;
				}
				else
					printf("%s\n", heredoc_text);
				if (h_d == -1)
					printf("can´t open heredoc file");
				if (dup2(d->stdout_copy, STDOUT_FILENO) == -1)
				{
					perror("Error al restaurar la salida estándar original");
					exit(1);
				}
				free(heredoc_text);
			}
			close(d->out);
			d->pipe[pipe].tokens[i + 1].token = d->tempfilename;
			update_redirections(d, pipe, i, DATA_INPUT);
*/		

#include "minishell.h"

void	parse_redirection(t_mini_data *data, int redirection)
{
	if (redirection == WRITE)
		open_redirection(data, redirection);
	else if (redirection == APPEND)
		open_redirection(data, redirection);
	else if (redirection == DATA_INPUT)
	{
		data->in = open(data->file_name, O_RDONLY, 0644);
		open_redirection(data, redirection);
	}
	else if (redirection == HERE_DOCUMENT)
	{
		data->in = open(data->tempfilename, O_RDONLY, 0644);
		if (data->in < 0)
		{
			perror("Error opening file Heredoc");
			exit(EXIT_FAILURE);
		}
		dup2(data->in, STDIN_FILENO);
		close(data->in);
	}
}

/* 			patch_heredoc(d, pipe, i, 0);
			reduce_heredoc_data(d, pipe, i);
			update_redirections(d, pipe, i, DATA_INPUT); 
*/

void	patch_redirections(t_mini_data *d, int pipe, int i)
{
	d->pipe[pipe].num_redirections = 0;
	d->pipe[pipe].num_commands = 0;
	while (i < d->pipe[pipe].num_tokens)
	{
		if (strncmp(d->pipe[pipe].tokens[i].token, "<<", 2) == 0)
		{
			printf("Heredoc not implemented\n");
			return ;
		}
		else if (strcmp(d->pipe[pipe].tokens[i].token, "<") == 0)
			update_redirections(d, pipe, i, DATA_INPUT);
		else if (strcmp(d->pipe[pipe].tokens[i].token, ">") == 0)
			update_redirections(d, pipe, i, WRITE);
		else if (strcmp(d->pipe[pipe].tokens[i].token, ">>") == 0)
			update_redirections(d, pipe, i, APPEND);
		else
		{
			d->pipe[pipe].num_commands++;
			d->pipe[pipe].tokens[i].redirection = COMMAND;
			i--;
		}
		i = i + 2;
	}
}

void	reduce_heredoc_data(t_mini_data *d, int pipe, int i)
{
	d->pipe[pipe].tokens[i].redirection = DATA_INPUT;
	d->pipe[pipe].tokens[i].token = "<";
	d->pipe[pipe].tokens[i + 1].token = d->tempfilename;
	d->pipe[pipe].tokens[i + 1].redirection = FILE_NAME;
	d->pipe[pipe].num_redirections++;
}
