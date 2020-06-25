/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 01:57:58 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/25 15:38:03 by hjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

int		ft_cd(char **argv)
{
	int		result;

	if (argv[1] && argv[2])
		return (CMD_ERR); // TOO MANY ARGUMENTS
	if (argv[1] == NULL)
		result = chdir("~");
	else
		result = chdir(argv[1]);
	// if (result == -1)
	// {
	// 	ft_putstr_fd("minishell: ", 1);
	// 	ft_putstr_fd(argv[0], 1);
	// 	ft_putstr_fd(": ", 1);
	// 	ft_putstr_fd(argv[1], 1);
	// 	ft_putstr_fd(": ", 1);
	// 	ft_putstr_fd(strerror(errno), 1);
	// }
	return (result);
}
