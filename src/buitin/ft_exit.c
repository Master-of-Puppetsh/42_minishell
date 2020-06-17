/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 15:16:43 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/17 16:08:27 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

int		ft_exit(char **argv)
{
	if (argv[1] && argv[2])
		return (ERROR); // TOO MANY ARGUMENT
	if (argv[])
		exit()
	return (SUCCESS);
}