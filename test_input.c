/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auskola- <auskola-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:37:03 by auskola-          #+#    #+#             */
/*   Updated: 2024/02/01 15:05:26 by auskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

	// faltan las señales
/*
 	d->test_mode_input[3] = \
	ft_strdup("ls | cat -e | ls -l | ls -l | grep b > a.txt");
	d->test_mode_input[4] = ft_strdup("< a.txt cat -e | grep m");
	d->test_mode_input[5] = ft_strdup("ls > a2.txt | ls cat -e >a.txt");
	d->test_mode_input[6] = ft_strdup("ls > a2.txt | <a2.txt | cat -e >a.txt");
	d->test_mode_input[7] = ft_strdup("<a.txt cat -e ");
	d->test_mode_input[8] = ft_strdup("< aitor cat -e ");
	d->test_mode_input[9] = ft_strdup("ls > a2.txt | pwd | cat -e >a.txt");
	d->test_mode_input[10] = ft_strdup("ls | cat -e >a11.txt");
	d->test_mode_input[13] = ft_strdup("env");
	d->test_mode_input[11] = ft_strdup("unset \"LOCPATH_VSCODE_SNAP_ORIG\"");
	d->test_mode_input[12] = ft_strdup("export casa=pues_vale/");
	d->test_mode_input[14] = ft_strdup("export PATH=pues_vale/");
	d->test_mode_input[15] = ft_strdup("env");
	d->test_mode_input[16] = ft_strdup("exit");  */
	// faltan los de cd
/* void	parse_test_input(t_mini_data *d)
{
	int	i;

	d->last_input = 24;
	i = -1;
	d->test_mode_input = malloc(sizeof(char *) * d->last_input + 1);
	d->test_mode_input[i++] = ft_strdup("/bin/ls");
	d->test_mode_input[i++] = ft_strdup(" 	 	");
	d->test_mode_input[i++] = ft_strdup("/bin/date");
	d->test_mode_input[i++] = ft_strdup("echo -n");
	d->test_mode_input[i++] = ft_strdup("echo $?");
	d->test_mode_input[i++] = ft_strdup("echo");
	d->test_mode_input[i++] = ft_strdup("echo \"hola\" asdf");
	d->test_mode_input[i++] = ft_strdup("echo \'hola mas\'");
	d->test_mode_input[i++] = ft_strdup("/bin/ls filethatdoesntexis");
	d->test_mode_input[i++] = ft_strdup("cat lol.c | cat > lol.c");
	d->test_mode_input[i++] = ft_strdup("echo ’$USER'");
	d->test_mode_input[i++] = ft_strdup("echo \"$USER\"");
	d->test_mode_input[i++] = ft_strdup("env");
	d->test_mode_input[i++] = ft_strdup("export aitor=casa");
	d->test_mode_input[i++] = ft_strdup("env");
	d->test_mode_input[i++] = ft_strdup("unset aitor");
	d->test_mode_input[i++] = ft_strdup("env");
	d->test_mode_input[i++] = ft_strdup("pwd");
	d->test_mode_input[i++] = ft_strdup("ls");
	d->test_mode_input[i++] = ft_strdup("wc");
	d->test_mode_input[i++] = ft_strdup("awk");
	d->test_mode_input[i++] = ft_strdup("<<pepe | grep af");
	d->test_mode_input[i++] = ft_strdup("exit");
} */

void	free_test_input(t_mini_data *d)
{
	int	i;

	i = 0;
	while (i < d->last_input)
	{
		free(d->test_mode_input[i]);
		i++;
	}
	free(d->test_mode_input);
}

void	test_mode_exit(t_mini_data *data)
{
	int	i;

	i = 0;
	while (i < data->last_input)
	{
		free(data->test_mode_input[i]);
		i++;
	}
	free(data->test_mode_input);
	exit (0);
}
