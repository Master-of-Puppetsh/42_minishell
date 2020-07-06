/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 14:35:31 by hyekim            #+#    #+#             */
/*   Updated: 2020/07/02 16:47:50 by hjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

extern int	g_pid;

void		handle_sigint(int signum)
{
	if (g_pid > 0)
		kill(g_pid, SIGTERM);
	write(STDERR_FILENO, "\n", 1);
	if (g_pid == -1)
		prompt();
	(void)signum;
}

void		handle_sigquit(int signum)
{
	if (g_pid > 0)
	{
		kill(g_pid, SIGABRT);
		write(STDERR_FILENO, "Quit: 3\n", 8);
	}
	(void)signum;
}

void		listen_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}
