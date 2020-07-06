/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 15:29:37 by hjeon             #+#    #+#             */
/*   Updated: 2020/07/01 20:30:09 by hyekim           ###   ########.fr       */
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
			if (!ft_strncmp(name, *target, ft_strlen(name) + 1))
			{
				free((*envp)[i]);
				last_str = pop_string(*envp);
				(*envp)[i] = last_str;
			}
			free(name);
		}
		target++;
	}
	return (SUCCESS);
}
