/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 15:26:25 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/21 22:35:41 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			reset_std(t_list )
{
	
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

int			set_fds(t_redirection *redirection, char **cmd_argv, int arg_idx)
{
	int		is_append;
	char	*filepath;
	int		i;

	is_append = cmd_argv[arg_idx][0] == '>' ? 1 : 0;
	if (!(filepath = ft_strdup(cmd_argv[arg_idx] + is_append)))
		exit_with_err_msg(ERRMSG_MALLOC, CMD_ERR);
	if (*filepath == '\0' && cmd_argv[arg_idx + 1] != NULL)
	{
		if (!(filepath = ft_strdup(cmd_argv[arg_idx + 1])))
			exit_with_err_msg(ERRMSG_MALLOC, CMD_ERR);
		free(cmd_argv[arg_idx + 1]); 
		i = 2;
		while (*(cmd_argv + arg_idx + i))
		{
			cmd_argv[arg_idx + i - 1] = cmd_argv[arg_idx + i]; 
			i++;
		}
		cmd_argv[arg_idx + i - 1] = NULL;
	}
	redirection->fd = open(filepath, O_RDWR | O_CREAT | O_APPEND * is_append);
	if (redirection->fd == ERROR)
		return (ERROR);
	redirection->copied_std = dup(STDOUT_FILENO);
	dup2(redirection->fd, STDOUT_FILENO);
}


int		create_redirection_list(t_list **begin_list, char **cmd_argv)
{
	t_redirection	*redirection;
	t_list			*new_list;
	int				i;
	int				j;

	i = 0;
	while (cmd_argv[i])
	{
		if ((j = find_redirection_mark(cmd_argv[i])) == FAIL)
			break ;
		if (!(redirection = malloc(sizeof(t_redirection))))
			exit_with_err_msg(ERRMSG_MALLOC, CMD_ERR);
		redirection->is_stdout = check_stdout(cmd_argv[i] + j);
		if (set_fds(redirection, cmd_argv, i) == ERROR)
		{
			reset_std(begin_list);
			free(redirection);
			return (ERROR);
		}
		if (!(new_list = ft_lstnew(redirection)))
			exit_with_err_msg(ERRMSG_MALLOC, CMD_ERR);
		ft_lstadd_back(&begin_list, new_list);
		cmd_argv[i++][j] = '\0';
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
			if (create_redirection_list(cmd_argv) == ERROR)
			{
				ft_putendl_fd(strerror(errno));
				continue;
			}
			execute_builtin(cmd_argv, &envp, &status);
			if (status == CMD_NOT_FOUND)
				execute_program(paths, cmd_argv, envp, &status);
			reset_std(redirection_list);
			if (is_redirection)
			{
				dup2(, STDOUT_FILENO);
				close(fd);
				// dup2(temp_stdin, STDIN_FILENO);
				// close(temp_stdin);
				// close(fd);
			}
		}
		free_split(commands);
	}
	return (status);
}
