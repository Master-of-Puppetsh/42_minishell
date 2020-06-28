/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 20:49:56 by hjeon             #+#    #+#             */
/*   Updated: 2020/06/28 21:59:42 by hjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

void		do_piping(int fds[])
{
	dup2(fds[0], STDIN_FILENO);
	dup2(fds[1], STDOUT_FILENO);
}

int	execute_pipeline(char **pipelines, char *envp[],
							int *prev, int temp_stdout)
{
	int		fds[2];
	int		pid;
	int		status;

	status = 0;
	if (*(pipelines + 1))
		pipe(fds);
	else
		fds[1] = temp_stdout;
	pid = fork();
	if (pid == 0)
	{
		status = execute_command_internal(*pipelines, &envp, status,
										(int[]){*prev, fds[1]});
		exit(status);
	}
	close(*prev);
	*prev = fds[0];
	close(fds[1]);
	return (pid);
}

int		execute_pipelines(char **pipelines, char *envp[], int status)
{
	int		prev;
	int		pid;
	int		temp_stdout;
	int		temp_stdin;

	prev = STDIN_FILENO;
	temp_stdout = dup(STDOUT_FILENO);
	temp_stdin = dup(STDIN_FILENO);
	while (*pipelines)
	{
		pid = execute_pipeline(pipelines, envp, &prev, temp_stdout);
		pipelines++;
	}
	waitpid(pid, &status, 0);
	do_piping((int[]){temp_stdin, temp_stdout});
	close(temp_stdin);
	close(temp_stdout);
	return (WEXITSTATUS(status));
}
