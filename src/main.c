/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 15:26:25 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/26 18:42:48 by hjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_pid = -1;

void		reset_std(t_list *list)
{
	t_redirection	*redirection;

	while (list)
	{
		redirection = list->content;
		dup2(redirection->copied_std, redirection->is_stdout);
		close(redirection->fd);
		close(redirection->copied_std);
		list = list->next;
	}
}

int			find_redirection_mark(char *str)
{
	int			i;

	i = 0;
	while (*(str + i))
	{
		if (*(str + i) == '>' || *(str + i) == '<')
			return (i);
		i++;
	}
	return (FAIL);
}

int		check_stdout(char *str)
{
	if (*str == '>')
		return (STDOUT_FILENO);
	else if (*str == '<')
		return (STDIN_FILENO);
	exit_with_err_msg("CHECK STDOUT ERR", CMD_ERR);
	return (ERROR);
}

void		remove_tab(char **argv, int idx)
{
	int		i;

	free(argv[idx]);
	i = 1;
	while (*(argv + idx + i))
	{
		argv[idx + i - 1] = argv[idx + i];
		i++;
	}
	argv[idx + i - 1] = NULL;
}

int			set_fds(t_redirection *redirection, char **cmd_argv, int arg_idx)
{
	int		is_append;
	int		mark_idx;
	char	*filepath;

	mark_idx = find_redirection_mark(cmd_argv[arg_idx]);
	is_append = cmd_argv[arg_idx][mark_idx + 1] == '>' ? 1 : 0;
	if (!(filepath = ft_strdup(cmd_argv[arg_idx] + is_append + mark_idx + 1)))
		exit_with_err_msg(ERRMSG_MALLOC, CMD_ERR);
	if (*filepath == '\0' && cmd_argv[arg_idx + 1] != NULL)
	{
		if (!(filepath = ft_strdup(cmd_argv[arg_idx + 1])))
			exit_with_err_msg(ERRMSG_MALLOC, CMD_ERR);
		remove_tab(cmd_argv, arg_idx + 1);
	}
	redirection->fd = open(filepath, O_RDWR | O_CREAT * redirection->is_stdout |
					O_TRUNC * !is_append * redirection->is_stdout |
					O_APPEND * is_append, 0777);
	if (redirection->fd == ERROR)
		return (ERROR);
	redirection->copied_std = dup(redirection->is_stdout);
	dup2(redirection->fd, redirection->is_stdout);
	return (SUCCESS);
}

int		free_redirection(t_list **begin_list, t_redirection *redirection)
{
	reset_std(*begin_list);
	free(redirection);
	return (ERROR);
}

int		create_redirection_list(t_list **begin_list, char **cmd_argv)
{
	t_redirection	*redirection;
	t_list			*new_list;
	int				i;
	int				j;

	i = -1;
	while (cmd_argv[++i])
	{
		if ((j = find_redirection_mark(cmd_argv[i])) == FAIL)
			continue ;
		if (!(redirection = malloc(sizeof(t_redirection)))
			|| !(new_list = ft_lstnew(redirection)))
			exit_with_err_msg(ERRMSG_MALLOC, CMD_ERR);
		redirection->is_stdout = check_stdout(cmd_argv[i] + j);
		if (set_fds(redirection, cmd_argv, i) == ERROR)
			return (free_redirection(begin_list, redirection));
		ft_lstadd_front(begin_list, new_list);
		cmd_argv[i][j] = '\0';
		if (cmd_argv[i][0] == '\0')
			remove_tab(cmd_argv, i);
	}
	return (SUCCESS);
}

int		execute_command_internal(char *command, char *envp[], int status, int fds[])
{
	char	**cmd_argv;
	t_list	*redirection_list;

	cmd_argv = parse_command(command, envp, status);
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
	{
		do_piping(fds);
		execute_builtin(cmd_argv, &envp, &status);
		if (status == CMD_NOT_FOUND)
			execute_program(cmd_argv, envp, &status);
		if (redirection_list)
			exit(status);
	}
	reset_std(redirection_list);
	ft_lstclear(&redirection_list, &free);
	g_pid = -1;
	return (status);
}

int		execute_pipelines(char **pipelines, char *envp[], int status)
{
	int		prev;
	int		pid;
	int		fds[2];
	int		temp_stdout;
	int		temp_stdin;

	prev = STDIN_FILENO;
	temp_stdout = dup(STDOUT_FILENO);
	temp_stdin = dup(STDIN_FILENO);
	while (*pipelines)
	{
		if (*(pipelines + 1))
			pipe(fds);
		else
			fds[1] = temp_stdout;
		pid = fork();
		if (pid == 0)
		{
			status = execute_command_internal(*pipelines, envp, status, (int[]){prev, fds[1]});
			exit(status);
		}
		close(prev);
		prev = fds[0];
		close(fds[1]);
		pipelines++;
	}
	waitpid(pid, &status, 0);
	do_piping((int[]){temp_stdin, temp_stdout});
	close(temp_stdin);
	close(temp_stdout);
	return (status);
}

void		do_piping(int fds[])
{
	dup2(fds[0], STDIN_FILENO);
	dup2(fds[1], STDOUT_FILENO);
}

int			main(int argc, char *argv[], char *envp[])
{
	char	*line;
	char	**commands;
	int		status;
	int		i;
	char	**pipelines;

	status = 0;
	listen_signals();
	while (argc == 1 && *argv)
	{
		prompt();
		line = read_command_line();
		if (!(commands = split_command(line, ';')))
			return (1);
		i = -1;
		while (*(commands + ++i))
		{
			if (*((pipelines = split_command(*(commands + i), '|')) + 1))
				status = execute_pipelines(pipelines, envp, status);
			else
				status = execute_command_internal(*(commands + i), envp, status, (int[]){STDIN_FILENO, STDOUT_FILENO});
		}
		free_split(commands);
	}
	return (status);
}
