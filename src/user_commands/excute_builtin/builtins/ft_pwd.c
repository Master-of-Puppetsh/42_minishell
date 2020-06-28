/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 02:18:24 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/28 21:05:49 by hjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

int		ft_pwd(int fd)
{
	char	path[1024];

	if (getcwd(path, 1024) == NULL)
		return (CMD_ERR);
	ft_putendl_fd(path, fd);
	return (SUCCESS);
}
