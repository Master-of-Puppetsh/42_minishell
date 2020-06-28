/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 20:25:19 by hjeon             #+#    #+#             */
/*   Updated: 2020/06/28 22:15:56 by hjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_pid;

int		execute_command(char *command, char ***envp, int status)
{
	char	**pipelines;

	if (*((pipelines = split_command(command, '|')) + 1))
		status = execute_pipelines(pipelines, *envp, status);
	else
		status = execute_command_internal(command, envp, status,
								(int[]){STDIN_FILENO, STDOUT_FILENO});
	free_split(pipelines);
	return (status);
}

int		do_execute_command_internal(char **cmd_argv, char **envp,
									int fds[], t_list *redirection_list)
{
	int		status;

	status = 0;
	if (!redirection_list)
		do_piping(fds);
	execute_builtin(cmd_argv, &envp, &status);
	if (status == CMD_NOT_FOUND)
		execute_program(cmd_argv, envp, &status);
	if (status == CMD_NOT_FOUND)
	{
		ft_putstr_fd(cmd_argv[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
	}
	if (redirection_list)
		exit(status);
	return (status);
}

int		execute_command_internal(char *command, char ***envp, int status,
									int fds[])
{
	char	**cmd_argv;
	t_list	*redirection_list;

	cmd_argv = parse_command(command, *envp, status);
	redirection_list = NULL;
	g_pid = 0;
	if (create_redirection_list(&redirection_list, cmd_argv) == ERROR)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return (CMD_ERR);
	}
	if (redirection_list)
	{
		if ((g_pid = fork()) > 0)
			wait(&status);
		status = WEXITSTATUS(status);
	}
	if (g_pid == 0)
		status = do_execute_command_internal(cmd_argv, *envp,
												fds, redirection_list);
	reset_std(redirection_list);
	ft_lstclear(&redirection_list, &free);
	g_pid = -1;
	free_split(cmd_argv);
	return (status);
}
