/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 22:05:37 by jsanger           #+#    #+#             */
/*   Updated: 2023/11/27 21:08:47 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define HERE_PATH ".here_document1234567890.txt"

# include <stdio.h>
# include <limits.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include "../libft/srcs/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_shell
{
	char	**env;
	char	*input;
	int		tokens;
	int		has_single_quote;
	int		heredoc_fd;
	int		is_heredoc;
	int		heredoc_ok;
	int		is_builtin;
	int		is_running;
	int		is_pipe;
	int		pipe_builtin;
	int		exitcode;
	char	cur_path[1024];
	char	*usr_path;
	char	*own_path;
	char	*shell_name;
	int		is_cat;
	int		stdout_saved;
	int		stdin_saved;
	int		outfile;
	int		infile;
}		t_shell;

bool		quote_check(t_shell *sh);
int			loop(t_shell *sh);
void		init(t_shell *sh, int argc, char **argv, char **env);
// utils
char		**get_env(char **env_stack);
void		free_2d_array(char **arr);
int			array_2d_len(char **arr);
bool		quote_check(t_shell *sh);
void		check_input(t_shell *sh, char *input);
char		*ft_strjoin_nl(char *old, char *line);
bool		ft_boolstrchr(const char *s, int c);
void		check_builtins(t_shell *sh, char **command);
void		ft_free(char *str);

// get_path
char		*get_path(char *cmd, char **env);
char		*ft_getenv(char **env, char *path);

// execute
void		exec(t_shell *sh, char *cmd);
void		ft_no_tokens(t_shell *sh);

// helper
const		char	*set_pathname(t_shell *sh);
char		*get_last_pathname(char *str);
char		*ft_remove_until(char *str, char c, int times);
int			ft_strlen_until_c(char *str, char c);

// only_pipe
bool		check_if_only_pipe(t_shell *sh);
void		combine_lst(t_shell *sh, int pipe_count);

//pipex
void		make_children(t_shell *sh, char *cmd);
void		pipex(int ac, char **av, t_shell *sh);

// builtin
void		own_cd(t_shell *sh);

void		own_export(t_shell *sh, char **command, int is_allocated);
void		own_export_helper(t_shell *sh, char *command, int is_allocated);
int			ft_valid_identifier(char *command, char *set);

void		own_env(t_shell *sh);
void		own_pwd(t_shell *sh);
void		own_unset(t_shell *sh, char **command);

void		own_echo(t_shell *sh, char **command, int is_splitted);
void		own_dollar(t_shell *sh, char *command);
char		**split_including(char *command, char c);
int			ft_strcontainchar(char *command, char c);
int			ft_strcontain(char *command);

// modded_split_for_qoutes
char		*ft_strtrim_mod(char *s1, char c);
char		*ft_strtrim_mod(char *s1, char c);
int			strlen_first_qoute(char *str);
int			ft_strlenchar(char *input);

char		first_qoute(char *s);
int			strlen_first_qoute(char *str);
int			count_dqoutes(char *input, int i);
int			count_sqoutes(char *input, int i);
int			ft_strlenchar(char	*input);
char		**parse_input(char *input, int diff);
char		*trim_and_conect(char **s);
char		**der_grosse_bruder(char *cmd);
// modded_split_lst
char		*connect(char *input);
int			length_qoutes(char *s);
char		**get_pipe_split(char *input);

// redirects
int			cut_redir_outfile(char *cmd, char c);
int			first_redir(char *cmd, char c);
int			is_last_builtin_1(t_shell *sh, char **command);
int			get_file(char *cmd, char c);
char		*is_last_redir(char *cmd, char c, int i, int check);
int			cut_string_infile(char *str, int start, int end, char c);
int			check_perm_or_file_1(int fd, char *str);
int			check_perm_or_file_2(int fd, char *str);
int			cut_string(char *str, int start, int end, char c);
int			cut_string_appendend(char *str, int start, int end, char c);
bool		redir_test(t_shell *sh);
void		reset_fd(t_shell *sh);
void		redir_out(t_shell *sh, char *cmd);
void		redir_in(t_shell *sh, char *cmd);
//redir utils
int			count_while_in_qoutes(char *cmd, char c, int i);

// heredoc
void		heredoc(t_shell *sh);
char		**kleiner_zwilling(char **command);

#endif