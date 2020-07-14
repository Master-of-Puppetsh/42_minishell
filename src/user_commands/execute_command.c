/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 20:25:19 by hjeon             #+#    #+#             */
/*   Updated: 2020/07/09 22:59:00 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_pid;

int			execute_command(char *command, char ***envp, int status)
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

void		remove_escapes(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i] != '\0')
	{
		quote = check_quote(str, quote, i);
		if (i > 0 && quote != 1 && quote != '\'' && str[i - 1] == '\\'
			&& (is_in_charset(str[i], "$\\\"") || quote == 0))
		{
			if (str[i] == '\'' || str[i] == '\"' || str[i] == '\\')
				str[i] -= 100;
			ft_memmove(str + i - 1, str + i, ft_strlen(str + i) + 1);
			i--;
		}
		i++;
	}
}

void		remove_quotes(char *str)
{
	char	quote;
	int		i;

	quote = 0;
	i = 0;
	while (str[i] != '\0')
	{
		quote = check_quote_passing_escape(str, quote, i);
		if ((str[i] == '\'' || str[i] == '\"')
				&& (quote == str[i] || quote == 1))
		{
			if (!(0 < i && str[i - 1] == '\\') ||
					(quote == 1 && str[i + 1] == '\0'))
			{
				ft_memmove(str + i, str + i + 1, ft_strlen(str + i + 1) + 1);
				i--;
			}
		}
		if (quote == 1)
			quote = 0;
		i++;
	}
}

int			do_execute_command_internal(char **cmd_argv, char ***envp,
									t_list *redirection_list)
{
	int		status;
	int		i;

	i = 0;
	status = 0;
	while (cmd_argv[i])
		clean_arg(cmd_argv[i++]);
	execute_builtin(cmd_argv, envp, &status);
	if (status == CMD_NOT_FOUND)
		execute_program(cmd_argv, *envp, &status);
	if (status == CMD_NOT_FOUND)
	{
		if (is_in_charset('/', cmd_argv[0]))
			print_error(cmd_argv[0], NULL, "No such file or directory");
		else
			print_error(cmd_argv[0], NULL, "command not found");
	}
	if (redirection_list)
		exit(status);
	return (status);
}

int			execute_command_internal(char *command, char ***envp, int status,
									int fds[])
{
	char	**cmd_argv;
	t_list	*redirection_lst;

	cmd_argv = parse_command(command, *envp, status);
	redirection_lst = NULL;
	g_pid = 0;
	do_piping(fds);
	if (create_redirection_list(&redirection_lst, cmd_argv) == ERROR)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return (CMD_ERR);
	}
	if (redirection_lst)
	{
		if ((g_pid = fork()) > 0)
			waitpid(g_pid, &status, 0);
		status = WEXITSTATUS(status);
	}
	if (g_pid == 0)
		status = do_execute_command_internal(cmd_argv, envp, redirection_lst);
	reset_std(redirection_lst);
	ft_lstclear(&redirection_lst, &free);
	g_pid = -1;
	free_split(cmd_argv);
	return (status);
}
