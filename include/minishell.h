/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 15:39:24 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/17 16:07:54 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef MINISHELL_H
#	define MINISHELL_H
#	define ERROR -1
#	define SUCCESS 0
#	include <stdio.h>
#	include <sys/wait.h>
#	include <sys/types.h>
#	include "./get_next_line.h"
#	include "./libft.h"

#	define SUCCESS	0
#	define ERROR	-1
#	define FAIL		-2

char	**init_env(char *envp[]);
void	*free_split(char **splitted_str);
char	**split_command(char *str);
char	*get_name(char *str);
int		ft_export(char *str, char *envp[]);
int		ft_env(char *envp[]);
int		ft_unset(char *target, char *envp[]);
int		find_env_index(char *name, char *envp[]);
int		expand_envp(char	***envp);
int		insert_string(char **envp, int	idx, char *str);
char	*pop_string(char **envp);



#	endif
