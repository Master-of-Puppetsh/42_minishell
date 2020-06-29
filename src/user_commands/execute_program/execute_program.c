/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_program.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 19:57:34 by hjeon             #+#    #+#             */
/*   Updated: 2020/06/29 16:04:18 by hjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

extern int	g_pid;

void		execute_program(char **argv, char **envp, int *status)
{
	char		**paths;
	char		*joined_path;
	int			i;

	if (!(paths = get_paths(envp)))
		return ;
	g_pid = fork();
	if (g_pid > 0)
	{
		waitpid(g_pid, status, 0);
		*status = WEXITSTATUS(*status);
	}
	else if (g_pid == 0)
	{
		i = 0;
		while (*(paths + i))
		{
			if (!(joined_path = ft_strjoin(*(paths + i++), argv[0])))
				exit_with_err_msg(ERRMSG_MALLOC, CMD_ERR);
			execve(joined_path, argv, envp);
			free(joined_path);
		}
		exit(CMD_NOT_FOUND);
	}
	free_split(paths);
}
