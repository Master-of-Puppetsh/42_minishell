/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 15:39:24 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/21 22:38:24 by hyekim           ###   ########.fr       */
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
#	include "./get_next_line.h"
#	include "./libft.h"

#	define SUCCESS			0
#	define ERROR			-1
#	define FAIL				-2
#	define CMD_NOT_FOUND	127
#	define CMD_ERR			1
#	define ERRMSG_MALLOC	"ERROR: failed to malloc"

typedef struct		s_redirection
{
	int				copied_std;
	int				is_stdout;
	int				fd;
}					t_redirection;

char	**init_env(char *envp[]);
void	*free_split(char **splitted_str);
char	**split_command(char *str);
char	*get_name(char *str);
int		ft_cd(char **argv);
int		ft_echo(char **argv);
int		ft_exit(char **argv, int status);
int		ft_pwd(char **argv);
int		ft_export(char **str, char ***envp);
int		ft_env(char *envp[]);
int		ft_unset(char **target, char ***envp);
int		find_env_index(char *name, char *envp[]);
int		expand_envp(char	***envp);
int		insert_string(char **envp, int	idx, char *str);
char	*pop_string(char **envp);
void	execute_program(char **paths, char **argv, char *envp[], int *status);
void	execute_builtin(char **argv, char ***envp, int *status);
char	*ft_getenv(char *name, char **envp);
void	exit_with_err_msg(char *msg, int status);
char	**parse_command(char *command, char **envp, int status);

#	endif
