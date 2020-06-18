/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_program.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 19:57:34 by hjeon             #+#    #+#             */
/*   Updated: 2020/06/18 22:09:42 by hjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		execute_program(char **paths, char **argv, char *envp[], int *status)
{
	int			pid;
	int			stat_loc;

	pid = fork();
	if (pid > 0)
		wait(&stat_loc);
	while (*(paths))
	{
		if (pid == 0)
			execve(ft_strjoin(*(paths), argv[0]), argv, envp);
		paths++;
	}
	if (pid == 0)
		exit(0);
}
