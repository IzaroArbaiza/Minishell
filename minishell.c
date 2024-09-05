/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarbaiza <iarbaiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:30:07 by auskola-          #+#    #+#             */
/*   Updated: 2024/02/02 17:05:56 by iarbaiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_config(t_mini_data *d)
{
	d->debug = 0;
	d->test_mode = 0;
	setbuf(stdout, NULL);
	d->add_export = 0;
	d->add_unset = 0;
	d->input = "";
	d->tempfilename = "_tempfile";
	d->env_key = 0;
	d->exit_now = 0;
	d->exit_number = 0;
	ft_signal();
}

/*
		d.input = "pwd | cat -e";
		d.input = "ls | cat -e";
		d.input = "ls | cat -e >a.txt";
		d.input = "ls > a2.txt | pwd | cat -e >a.txt";
		d.input = "ls >> a2.txt | pwd | cat -e >>a.txt";
		d.input = "pwd >> a2.txt | ls -la | cat -e >>a.txt";
		d.input = "< a2.txt | cat -e";
*/

	//	d->test_mode_input[10] = ft_strdup("ls | cat -e >a11.txt");
	//	d->test_mode_input[11] = ft_strdup("unset \"TERM_PROGRAM\"");
	//	d->test_mode_input[12] = ft_strdup("env");
	//	d->test_mode_input[12] = ft_strdup("exit");
	//	d->test_mode_input[13] = ft_strdup("env");
	//	d->test_mode_input[14] = ft_strdup("exit");

int	main(int argc, char **argv, char **envp)
{
	t_mini_data	d;

	start_config(&d);
	parse_envp2(&d, envp);
	while (1)
	{
		d.input = readline("minishell IA :) ");
		if (!d.input)
			exit (1);
		if (ft_strlen(d.input) > 0)
		{
			if (check_input_invalid(&d, 0, 0))
				break ;
			d.invalid = check_input_errors(&d);
			if (d.invalid == 1)
				break ;
			else if (d.invalid != 2)
				reduce_main(&d);
			if (d.exit_now == 1)
				break ;
		}
	}
	free_env_(&d);
	return ((void)argv, (void)argc, d.exit_number);
}

//		line_free(d);  // no se si es necesario despues del parseline
void	reduce_main(t_mini_data *d)
{
	add_history(d->input);
	if (strcmp(d->input, "") != 0)
	{
		parse_line(d);
	}
	if (strcmp(d->input, "") != 0)
		free_pipes(d);
	free(d->input);
}

int	check_input_errors(t_mini_data *data)
{
	char	*k;

	k = ft_strtrim(data->input, " ");
	if (ft_strlen(k) < 2)
		return (2);
	data->str = ft_substr(data->input, 0, 6);
	if (strncmp(data->str, "exit ", 5) == 0 || strcmp(data->str, "exit") == 0)
	{
		if (ft_strlen(data->str) > 5)
		{
			if ((data->str[5] >= '0') && (data->str[5] <= '9'))
			{
				data->exit_now = 1;
				k = ft_substr(k, 5, ft_strlen(k));
				data->exit_number = atoi(k);
				return (free(data->str), 2);
			}
			else
				return (printf("Invalid exit, numeric argument \
				required\n"), free(data->str), 2);
		}
		return (free(data->str), 1);
	}
	return (free(data->str), 0);
}

int	check_input_invalid(t_mini_data *data, int incorrect, unsigned long counter)
{
	if (ft_strlen(data->input) == 1)
		return (1);
	if (g_signals > 0)
		data->wait_pid = g_signals;
	g_signals = 0;
	while (counter < (ft_strlen(data->input)))
	{
		if (data->input[counter] == '"' || data->input[counter] == '\'')
		{
			if (counter > 0)
			{
				if (data->input[counter - 1] != '\\')
					incorrect++;
			}
			else
				incorrect++;
		}
		counter++;
	}
	if (incorrect % 2 == 1)
	{
		printf("Invalid imput Quotes\n");
		return (1);
	}
	return (0);
}
