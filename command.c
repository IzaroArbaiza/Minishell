/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auskola- <auskola-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 09:27:53 by auskola-          #+#    #+#             */
/*   Updated: 2024/02/02 15:21:47 by auskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* 	
	//	printf("Comandos %d\n", data->pipe[line_number].num_commands);
	//	argv[j] = ft_strdup(data->pipe[line_number].tokens[i].token);
	//	data->file_name =\
	//	ft_strdup(data->pipe[line_number].tokens[i + 1].token);
	//	printf("File name: %s\n", data->file_name);
	//	parse_redirection(data, line_number, i);
	//	argv[j] = ft_strdup(data->pipe[line_number].tokens[i].token);
	//	data->file_name =\ 
	// 	ft_strdup(data->pipe[line_number].tokens[i + 1].token);
	//	printf("File name: %s\n", data->file_name);
	//	parse_redirection(data, line_number, i);
	//	argv[j] = ft_strdup(data->pipe[line_number].tokens[i].token);
	//	data->file_name =\
	//	ft_strdup(data->pipe[line_number].tokens[i + 1].token);
	//	printf("File name: %s\n", data->file_name);
	//	printf("File name: %s\n", data->tempfilename);
	// 	printf("%s\n",clean_text(data, line_number,i));

		if (type == WRITE)
			{
				data->file_name = clean_text(data, pipe, i + 1);
				parse_redirection(data, WRITE);
				i++;
			}
			if (type == APPEND)
			{
				data->file_name = clean_text(data, pipe, i + 1);
				parse_redirection(data, APPEND);
				i++;
			}
			if (type == DATA_INPUT)
			{
				data->file_name = clean_text(data, pipe, i + 1);
				parse_redirection(data, DATA_INPUT);
				i++;
			}
			if (type == HERE_DOCUMENT)
			{
//				exit (0);
				parse_redirection(data, HERE_DOCUMENT);
				i++;
			} 			
			
			
*/
/*
		if (data->debug)
			printf("Comprobado tipo token: %d\n", type);
*/			
char	**get_arg(t_mini_data *data, int pipe, int i, int j)
{
	char	**argv;
	int		type;

	argv = malloc(sizeof(char *) *(data->pipe[pipe].num_commands + 1));
	while (i < data->pipe[pipe].num_tokens)
	{
		type = data->pipe[pipe].tokens[i].redirection;
		if (type == COMMAND)
		{
			argv[j] = clean_text(data, pipe, i);
			j++;
		}
		if (i < data->pipe[pipe].num_tokens - 1 && type >= 1 && type <= 4)
		{
			data->file_name = clean_text(data, pipe, i + 1);
			parse_redirection(data, type);
			i++;
		}
		i++;
	}
	argv[j] = NULL;
	if (j == 0)
		return (free(argv), argv = NULL, argv);
	return (argv);
}

//	data->wait_pid = 0;
//	printf("Errora: %d\n", wait_pid );
//	printf("Command not found, error\n");
//		printf("KJA:%d ", 127);
//		printf(" --%d\n", WEXITSTATUS(data->exit_number));

void	execute_command(t_mini_data *data, int pipe_number)
{
	char	**argv;

	patch_redirections(data, pipe_number, 0);
	argv = get_arg(data, pipe_number, 0, 0);
	if (!argv)
		return ;
	if (execute_builtin(data, argv, pipe_number) == 1)
		data->i = 0;
	else if (check_path(data, argv[0]) == 1)
	{
		make_env_join(data);
		if (execve(data->exec_path, argv, data->envp) == -1)
		{
			perror("Command error:");
		}
		make_env_split(data);
	}
	else
	{
		data->exit_number = 127;
		perror("Command not found, error");
		exit (127);
	}
	free_argv(argv);
}
