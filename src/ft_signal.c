/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 14:35:31 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/26 18:45:03 by hjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

extern int g_pid;

void	handle_sigint(int signum)
{
	if (g_pid > 0)
		kill(g_pid, SIGTERM);
	write(STDERR_FILENO, "\n", 1);
	if (g_pid == -1)
		write(STDERR_FILENO, "$ ", 2);
	(void)signum;
}

// void	handle_eof(int signum)
// {
// 	if (g_pid == -1)
// 	{
// 		write(STDERR_FILENO, "exit\n", 5);
// 		exit(0);
// 	}

// }

void			handle_sigquit(int signum)
{
	if (g_pid > 0)
	{
		kill(g_pid, SIGABRT);
		write(STDERR_FILENO, "Quit\n", 5);
	}
	(void)signum;
}

void			listen_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}
