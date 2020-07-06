/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 15:39:24 by hyekim            #+#    #+#             */
/*   Updated: 2020/07/06 16:14:46 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef MINISHELL_H
#	define MINISHELL_H

#	include <stdio.h>
#	include <sys/wait.h>
#	include <sys/types.h>
#	include <fcntl.h>
#	include <string.h>
#	include <errno.h>
#	include <signal.h>
#	include "./libft.h"

#	define SUCCESS			0
#	define ERROR			-1
#	define FAIL				-2
#	define CMD_NOT_FOUND	127
#	define CMD_ERR			1
#	define ERRMSG_MALLOC	"ERROR: failed to malloc"

typedef struct	s_redirection
{
	int			copied_std;
	int			is_stdout;
	int			fd;
}				t_redirection;

int				print_err_continous_semicolons(int err_type);
int				check_continuous_semicolons(char *line);
void			malloc_envp(char **envp);
void			do_piping(int fds[]);
char			**get_paths(char *envp[]);
void			*free_split(char **splitted_str);
char			**split_command(char *str, char target);
char			*get_name(char *str);
int				ft_cd(char **argv, char *envp[]);
int				ft_echo(char **argv);
int				ft_exit(char **argv, int status);
int				ft_pwd(int fd);
int				ft_export(char **str, char ***envp);
int				ft_env(char *envp[]);
int				ft_unset(char **target, char ***envp);
int				find_env_index(char *name, char *envp[]);
int				expand_envp(char	***envp);
int				insert_string(char **envp, int	idx, char *str);
char			*pop_string(char **envp);
void			execute_program(char **argv, char **envp, int *status);
void			execute_builtin(char **argv, char ***envp, int *status);
char			*ft_getenv(char *name, char **envp);
void			exit_with_err_msg(char *msg, int status);
char			**parse_command(char *command, char **envp, int status);
void			listen_signals(void);
char			*read_command_line(int status);
int				prompt(void);
char			check_quote(char *str, char quote, int idx);
int				execute_command(char *command, char ***envp, int status);
int				execute_command_internal(char *command, char ***envp,
											int status, int fds[]);
int				execute_pipelines(char **pipelines, char *envp[], int status);
void			do_piping(int fds[]);
int				create_redirection_list(t_list **begin_list, char **cmd_argv);
void			reset_std(t_list *list);
void			remove_tab(char **argv, int idx);
int				free_redirection(t_list **begin_list,
									t_redirection *redirection);
int				is_in_charset(char c, char *str);
char			*replace_text(char *dest, int start, int length, char *src);
int				do_replace_env(int i, char **arg, char **envp);
void			print_error(char *command, char *arg, char *errmsg);
int				replace_question_to_status(int status, int i, char **arg);
int				is_escape(int idx, char quote, char *str);
char			check_quote_passing_escape(char *str, char quote, int idx);
void			init_3vars_to_zero(char *var1, int *var2, int *var3);
void			make_quote_printable(char *str);

#	endif
