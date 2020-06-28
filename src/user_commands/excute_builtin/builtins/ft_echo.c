/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 15:00:21 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/26 15:39:03 by hjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

int		ft_echo(char **argv)
{
	int		i;
	int		is_n_option;

	i = 1;
	is_n_option = 0;
	while (argv[i] != NULL && ft_strncmp("-n", argv[i], 3) == 0)
	{
		is_n_option = 1;
		// printf("hi : %s\n", argv[i]);
		i++;
	}
	while (*(argv + i) != NULL)
	{
		ft_putstr_fd(*(argv + i), STDOUT_FILENO); // TODO : add space
		if (*(argv + i + 1) != NULL)
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (is_n_option == 0)
		write(1, "\n", 1);
	return (SUCCESS);
}
