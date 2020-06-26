/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 01:57:58 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/26 16:08:02 by hjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

int		ft_cd(char **argv, char *envp[])
{
	int		result;

	if (argv[1] && argv[2])
		return (CMD_ERR); // TOO MANY ARGUMENTS
	if (argv[1] == NULL)
		result = chdir(ft_getenv("HOME", envp));
	else
		result = chdir(argv[1]);
	return (result);
}
