/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 15:29:37 by hjeon             #+#    #+#             */
/*   Updated: 2020/07/17 20:38:49 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_unset(char **target, char ***envp)
{
	int		i;
	char	*name;
	char	*temp;

	while (*(++target))
	{
		i = -1;
		while ((*envp)[++i])
		{
			if (!(name = get_name((*envp)[i])))
				return (ERROR);
			if (!ft_strncmp(name, *target, ft_strlen(name) + 1))
			{
				temp = (*envp)[i];
				if ((*envp)[i + 1] != NULL)
					(*envp)[i] = pop_string(*envp);
				else
					(*envp)[i] = NULL;
				free(temp);
			}
			free(name);
		}
	}
	return (SUCCESS);
}
