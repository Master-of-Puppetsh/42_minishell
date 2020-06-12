/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 15:39:24 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/12 18:23:05 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef MINISHELL_H
#	define MINISHELL_H
#	include <stdio.h>
#	include <sys/wait.h>
#	include <sys/types.h>
#	include "./get_next_line.h"
#	include "./libft.h"

char	**init_env(char *envp[]);
void	free_split(char **splitted_str);

#	endif
