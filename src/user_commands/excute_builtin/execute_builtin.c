/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 20:16:26 by hjeon             #+#    #+#             */
/*   Updated: 2020/06/29 17:23:25 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void		print_error(char *command, char *arg, char *errmsg)
{
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (arg)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (errmsg)
		ft_putendl_fd(errmsg, STDERR_FILENO);
	else
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

void		execute_builtin(char **argv, char ***envp, int *status)
{
	if (ft_strncmp(argv[0], "echo", 5) == 0)
		*status = ft_echo(argv);
	else if (ft_strncmp(argv[0], "cd", 3) == 0)
		*status = ft_cd(argv, *envp);
	else if (ft_strncmp(argv[0], "pwd", 4) == 0)
		*status = ft_pwd(STDOUT_FILENO);
	else if (ft_strncmp(argv[0], "export", 7) == 0)
		*status = ft_export(argv, envp);
	else if (ft_strncmp(argv[0], "unset", 6) == 0)
		*status = ft_unset(argv, envp);
	else if (ft_strncmp(argv[0], "env", 4) == 0)
		*status = ft_env(*envp);
	else if (ft_strncmp(argv[0], "exit", 5) == 0)
		*status = ft_exit(argv, *status);
	else
		*status = CMD_NOT_FOUND;
}
