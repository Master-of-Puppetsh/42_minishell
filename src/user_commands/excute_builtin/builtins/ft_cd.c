/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 01:57:58 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/29 15:57:25 by hjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

int		ft_cd(char **argv, char *envp[])
{
	int		result;

	if (argv[1] == NULL)
		result = chdir(ft_getenv("HOME", envp));
	else
		result = chdir(argv[1]);
	if (result == ERROR)
		print_error("cd", argv[1], NULL);
	return (result * -1);
}
