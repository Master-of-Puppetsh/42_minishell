/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 15:26:25 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/17 16:08:41 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		execute_excutable(char **paths, char *line, char *envp[])
{
	char		**argv;
	int			pid;
	int			stat_loc;

	pid = fork();
	if (0 < pid)
		wait(&stat_loc);
	if (!(argv = ft_split(line, ' ')))
		return ; // error;
	while (*(paths))
	{
		if (pid == 0)
			execve(ft_strjoin(*(paths), argv[0]), argv, envp);
		paths++;
	}
	if (pid == 0)
		exit(0);
}

int			main(int argc, char *argv[], char *envp[])
{
	char	*line;
	int		result;
	char	**paths;
	char	**commands;
	int		i;

	paths = init_env(envp);
	line = NULL;
	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2);
		if ((result = get_next_line(STDIN_FILENO, &line)) == -1)
			return (1);
		if (result == 0)
			return (0);
		if (!(commands = split_command(line)))
			return (1);
		//commands의 환경변수를 value로 대치하기
		i = 0;
		while (*(commands + i))
		{
			// our_programs(paths, line);
			execute_excutable(paths, *(commands + i), envp);
			execute_builtin(*(commands + i), envp);
			i++;
		}
		free_split(commands);
	}
}
