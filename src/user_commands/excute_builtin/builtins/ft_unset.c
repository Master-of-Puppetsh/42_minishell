/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 15:29:37 by hjeon             #+#    #+#             */
/*   Updated: 2020/06/27 19:36:59 by hjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_unset(char **target, char ***envp)
{
	int		i;
	char	*name;
	char	*last_str;

	i = -1;
	target++;
	while (*target)
	{
		while ((*envp)[++i])
		{
			if (!(name = get_name((*envp)[i])))
				return (ERROR);
			printf("%s\n", name);
			printf("%s\n", *target);
			if (!ft_strncmp(name, *target, ft_strlen(name)))
			{
				last_str = pop_string(*envp);
				(*envp)[i] = last_str;
			}
		}
		target++;
	}
	return (SUCCESS);
}
