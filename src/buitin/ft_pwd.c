/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 02:18:24 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/17 14:58:45 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

void	ft_pwd(char **argv)
{
	char	**argv;
	char	path[1024];

	if (getcwd(path, 1024) == NULL)
		return ; // getcwd err
	ft_putstr_fd(path, 1);
}
