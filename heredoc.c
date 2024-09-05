/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auskola- <auskola-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:25:54 by auskola-          #+#    #+#             */
/*   Updated: 2024/01/04 15:58:32 by auskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	patch_heredoc(t_mini_data *data, int pipe_number, int i, int out)
{
	char	*compare_text;
	char	stdout_copy;

	compare_text = data->pipe[pipe_number].tokens[i + 1].token;
	stdout_copy = dup(STDOUT_FILENO);
	out = open(data->tempfilename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		data->heredoc_text = readline(">");
		if (!data->heredoc_text || \
		strcmp(data->heredoc_text, compare_text) == 0)
		{
			free(data->heredoc_text);
			break ;
		}
		fflush(stdout);
		dup2(out, STDOUT_FILENO);
		printf("%s\n", data->heredoc_text);
		fflush(stdout);
		dup2(stdout_copy, STDOUT_FILENO);
		free(data->heredoc_text);
	}
	close(out);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdout_copy);
}

int	patch_heredoc2(t_mini_data *data, int pipe_number, \
int i, char	*compare_text)
{
	int		h_d;

	if (!data->heredoc_text)
		return (0);
	if (strcmp(data->heredoc_text, compare_text) == 0)
	{
		dup2(data->stdout_copy, STDOUT_FILENO);
		return (0);
	}
	else
		printf("%s -  %s\n", data->heredoc_text, \
		data->pipe[pipe_number].tokens[i + 1].token);
	h_d = dup2(data->out, STDOUT_FILENO);
	if (h_d == -1)
	{
		printf("can´t open heredoc file");
		return (0);
	}
	return (1);
}
