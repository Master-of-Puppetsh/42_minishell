/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 15:16:43 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/26 16:28:50 by hjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#	include "minishell.h"

int		ft_exit(char **argv, int status)
{
	if (argv[1] && argv[2])
		return (CMD_ERR); // TOO MANY ARGUMENT
	ft_putendl_fd("exit", STDERR_FILENO);
	if (!argv[1])
		exit(status);
	exit(ft_atoi(argv[1]));
	return (SUCCESS);
}
