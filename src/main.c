/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 15:26:25 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/22 16:30:27 by hjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			reset_std(t_list *list)
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

int			check_stdout(char *str)
{
	if (*str == '>')
		return (STDOUT_FILENO);
	else if (*str == '<')
		return (STDIN_FILENO);
	exit_with_err_msg("CHECK STDOUT ERR", CMD_ERR);
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

int			main(int argc, char *argv[], char *envp[])
{
	char	*line;
	char	**paths;
	char	**commands;
	int		status;
	int		i;
	char	**cmd_argv;
	int		redirection_filename;
	int		temp_stdout;
	t_list	*redirection_list;

	paths = init_env(envp);
	status = 0;
	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2);
		if ((i = get_next_line(STDIN_FILENO, &line)) == -1 || i == 0)
			return (i * -1);
		if (!(commands = split_command(line)))
			return (1);
		i = -1;
		while (*(commands + ++i))
		{
			cmd_argv = parse_command(*(commands + i), envp, status);
			redirection_list = NULL;
			if (create_redirection_list(&redirection_list, cmd_argv) == ERROR)
			{
				ft_putendl_fd(strerror(errno), STDERR_FILENO);
				continue;
			}
			execute_builtin(cmd_argv, &envp, &status);
			if (status == CMD_NOT_FOUND)
				execute_program(paths, cmd_argv, envp, &status);
			reset_std(redirection_list);
			ft_lstclear(&redirection_list, &free);
		}
		free_split(commands);
	}
	return (status);
}
