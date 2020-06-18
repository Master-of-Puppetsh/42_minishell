/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 15:00:21 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/17 15:33:10 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

int		ft_echo(char **argv)
{
	int		i;
	int		is_n_option;

	i = 1;
	is_n_option = 0;
	if (argv[i] != NULL && ft_strncmp("-n", argv[i], 3) == 0)
	{
		is_n_option = 1;
		i++;
	}
	while (*(argv + i) != NULL)
	{
		ft_putstr_fd(*(argv + i), STDOUT_FILENO);
		i++;
	}
	if (is_n_option == 0)
		write(1, "\n", 1);
	return (SUCCESS);
}
