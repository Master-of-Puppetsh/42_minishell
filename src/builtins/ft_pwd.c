/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 02:18:24 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/22 14:27:57 by hjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

int		ft_pwd(char **argv)
{
	char	path[1024];

	if (getcwd(path, 1024) == NULL)
		return (CMD_ERR);
	ft_putendl_fd(path, 1);
	return (SUCCESS);
}
