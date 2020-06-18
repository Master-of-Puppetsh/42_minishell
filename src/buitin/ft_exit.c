/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 15:16:43 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/18 17:59:36 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

int		ft_exit(char **argv, int status)
{
	if (argv[1] && argv[2])
		return (ERROR); // TOO MANY ARGUMENT
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (!argv[1])
		exit(status);
	exit(ft_atoi(argv[1]));
}