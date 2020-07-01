/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirection_list.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 20:48:39 by hyekim            #+#    #+#             */
/*   Updated: 2020/07/01 20:49:47 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		find_redirection_mark(char *str)
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

int		set_fds(t_redirection *redirection, char **cmd_argv, int arg_idx)
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
		free(filepath);
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
	free(filepath);
	return (SUCCESS);
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
			remove_tab(cmd_argv, i--);
	}
	return (SUCCESS);
}
