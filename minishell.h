/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auskola- <auskola-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 09:40:15 by auskola-          #+#    #+#             */
/*   Updated: 2024/02/02 14:53:09 by auskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "./readline/readline.h"
# include "./readline/history.h"
// # include <readline/readline.h>
// # include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/ioctl.h>

typedef struct s_token
{
	char		*token;
	int			num_args;
	int			ent_var;
	int			redirection;
	int			token_type;
}	t_token;

typedef struct s_redirections
{
	char		**commands;
	int			num_args;
	int			ent_var;
	int			redirection;
}	t_redirections;

typedef struct s_pipe
{
	char			*line;
	int				num_tokens;
	t_token			*tokens;
	int				pipe_tipe;
	int				has_redirection;
	int				last_redirection;
	t_redirections	*redirections;
	int				num_redirections;
	int				num_commands;

}	t_pipe;

typedef struct s_env_data
{
	char	*key;
	char	*value;
}	t_env_data;

typedef struct s_mini_data
{
	int			history_lenght;
	char		*input;
	HIST_ENTRY	*history_lines;

	int			env_key;
	t_env_data	*env_data;
	t_env_data	*env_data_temp;
	char		**envp;
//	char		**env_array;	
	int			env_array_len;
	int			*fd;
	int			num_pipes;
	int			**pipes;
	int			is_single_quote;
	int			is_double_quote;
	int			is_backslash;
	int			input_buffer;
	pid_t		pid;
	char		*file_name;
	int			file_id;
	t_pipe		*pipe;
	char		**paths;	
	char		*path;	
	int			num_paths;
	char		*exec_path;
	char		*tempfilename;
	int			want_exit;
	int			i;
	int			j;
	int			in;
	int			out;
	int			stdout_copy;
	char		*heredoc_text;
	int			temp_pipes;
	int			pipe_len;
	char		*str;
	char		debug;
	char		test_mode;
	char		**test_mode_input;
	int			last_input;
	int			add_export;
	int			add_unset;
	int			max_env;
	int			tokens;
	int			token_len;
	int			exit_now;
	int			exit_number;
	int			wait_pid;
	int			invalid;
}	t_mini_data;

enum e_PIPE_TYPE
{
	PIPE = 0,
	WRITE = 1,
	APPEND = 2,
	DATA_INPUT = 3,
	HERE_DOCUMENT = 4,
	COMMAND = 5,
	FILE_NAME = 6,
	FILE_HEREDOC = 7
};

char	*ft_strdup(const char *str);
size_t	ft_count_strings(const char *s, char c);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_get_line(char const *s, char c, int *mem_pos);
void	parse_line(t_mini_data *data);
void	signalquit_handler(int signal);
void	signalinterrupt_handler(int signal);
void	parse_command(t_mini_data *data);
int		execute_builtin(t_mini_data *data, char **argv, int pipe);
void	num_pipes(t_mini_data *data);
void	parse_pipes(t_mini_data *data);
void	num_tokens(t_mini_data *data, int pipe);
void	parse_tokens(t_mini_data *data, int pipe);
void	line_free(t_mini_data *data);
void	execute_command(t_mini_data *data, int pipe);
char	**get_arg(t_mini_data *data, int pipe, int i, int j);
void	free_argv(char **argv);
void	malloc_pipes(t_mini_data *data);
void	free_pipes(t_mini_data *data);
void	close_pipes(t_mini_data *data, int current_process);
int		ft_pwd(char **cmd);
void	free_cmd(char **cmd);
int		len_cmd(char **cmd);
int		ft_echo(char **args, t_mini_data *data);
void	parse_redirection(t_mini_data *data, int redirection);
void	close_redirection(t_mini_data *data);
void	parse_path(t_mini_data *data);
int		check_path(t_mini_data *data, char *argv);
char	*ft_strjoin(char const *s1, char const *s2);
void	token_free(t_mini_data *data, int i);
//void	check_redirection(t_mini_data *data, int pipe_number, int token);
void	patch_redirections(t_mini_data *data, int pipe_number, int i);
char	*check_need_quote(char *token_string);
char	*ft_strdup_trim(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
int		check_redirect(char **argv, int i);
char	*clean_text(t_mini_data *data, int line_number, int i);
char	*remove_quote(char *token_string, int len, int i);
int		check_input_errors(t_mini_data *data);
void	parse_helper(t_mini_data *data, int redirection);
void	patch_heredoc(t_mini_data *data, int pipe_number, int i, int out);
int		patch_redirection_pipe(t_mini_data *data, int pipe_number, \
int i, char *str_temp);
void	update_redirections(t_mini_data *data, int pipe, int i, int data_type);
void	open_redirection(t_mini_data *data, int redirection);
int		patch_heredoc2(t_mini_data *data, \
int pipe_number, int i, char *compare_text);
int		patch_redirections2(t_mini_data *d, int pipe, int i);
void	parse_pipes2(t_mini_data *data);
void	parse_check_quote(t_mini_data *data, int i);
void	parse_check_backslash(t_mini_data *data, int i);
void	parse_tokens2(t_mini_data *d);
void	parse_tokens_backslash(t_mini_data *d, int pipe);
void	clear_pipes(t_mini_data *data);
int		change_quote(int value);
void	debug_pipes(t_mini_data *data);
void	debug_tokens(t_mini_data *data, int pipe);
int		execute_builtin2(t_mini_data *data, char **args, int pipe);
void	parse_env(t_mini_data *data);
void	free_env(t_mini_data *data);
void	parse_envp(t_mini_data *data);
void	parse_envp2(t_mini_data *data, char **envp);
char	*get_key(char *str);
int		get_key_num(t_mini_data *data, char *key);
char	*get_value(char *str);
void	make_env_split(t_mini_data *data);
void	make_env_join(t_mini_data *data);
void	free_env_split(t_mini_data *data);
int		search_env(t_mini_data *data, char *key);
int		print_env_num(t_mini_data *data, int env_number);
int		unset_env(t_mini_data *data, char *key);
void	env_export(t_mini_data *data, char *key, char *value);
void	start_config(t_mini_data *d);
void	join_env_data(t_mini_data	*data, int i);
void	free_env_(t_mini_data *data);
char	*merge_env_data(t_mini_data	*data, int i);
int		is_builtin(t_mini_data *data, int pipe);
char	*check_names(char	*args);
int		is_repeated(char *args);
int		compar(char *args, const char *command);
int		compar2(char *args, const char *command);

void	reorder_command(t_mini_data *data, int pipe_number);
void	free_test_input(t_mini_data *d);
void	parse_test_input(t_mini_data *d);
void	env_show(t_mini_data *data);
void	test_mode_exit(t_mini_data *data);
void	initialize_parse_tokens(t_mini_data *data, int pipe);
int		reduce_line_numtokens1(t_mini_data *d, int pipe);
int		reduce_line_numtokens2(t_mini_data *d, int pipe);
int		reduce_parse_tokens_1(t_mini_data *data, int pipe);
int		reduce_parse_tokens_2(t_mini_data *data, int pipe);
int		reduce_parse_tokens_3(t_mini_data *data, int pipe);
int		reduce_parse_tokens_4(t_mini_data *data, int pipe);
void	reduce_parse_command1(t_mini_data *data);
void	reduce_parse_command2(t_mini_data *data);
void	reduce_parse_command_fd(t_mini_data *data);
void	reduce_parse_command_wait(t_mini_data *data);
void	reduce_heredoc_data(t_mini_data *d, int pipe, int i);
void	reduce_main(t_mini_data *d);
int		ft_cd(char **args);
int		cd_point_point(void);
int		cd_too_many(char **args);
char	*trim_path(char *path);
void	bubble_sort(t_mini_data *d, int swapped);
//void    bubble_sort(t_mini_data *d);
void	print_export(t_mini_data *data, t_env_data *bubble);
int		check_export(t_mini_data *data, char **args);
int		check_input_invalid(t_mini_data *data, \
int incorrect, unsigned long counter);
void	clear_quote(t_mini_data *data, int pipe, int token, int back_slash);
size_t	ft_posini(char const *s1, char const *set);
size_t	ft_endpos(char const *s1, char const *set);
char	*ft_strtrim(char const *s1, char const *set);
char	*get_env_by_id(t_mini_data *data, int pos);
int		ft_echo2(char **args, t_mini_data *data);
void	clear_tokens(t_mini_data *data, int pipe, int i, int counter);
void	ft_signal(void);

int	g_signals;
#endif