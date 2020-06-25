/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_program.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 19:57:34 by hjeon             #+#    #+#             */
/*   Updated: 2020/06/19 14:23:335 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void		execute_program(char **argv, char *envp[], int *status)
{
	int			pid;
	char		**paths;

	pid = fork();
	paths = get_paths(envp);
	if (pid > 0)
	{
		waitpid(pid, status, 0);
		*status = WEXITSTATUS(*status);
	}
	else if (pid == 0)
	{
		while (*(paths))
		{
			execve(ft_strjoin(*(paths), argv[0]), argv, envp);
			paths++;
		}
		exit(CMD_NOT_FOUND);
	}
}
