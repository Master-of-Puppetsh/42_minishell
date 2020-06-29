/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 14:55:31 by hjeon             #+#    #+#             */
/*   Updated: 2020/06/29 16:04:02 by hjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_export(char **str, char ***envp)
{
	int		idx;
	char	*name;
	int		cur_size;

	str++;
	while (*str)
	{
		if (!(name = get_name(*str)))
			return (ERROR);
		idx = find_env_index(name, *envp);
		if (idx < 0)
		{
			if ((cur_size = expand_envp(envp)) == ERROR)
			{
				free(name);
				return (ERROR);
			}
			insert_string(*envp, cur_size - 1, *str);
		}
		else
			insert_string(*envp, idx, *str);
		free(name);
		str++;
	}
	return (SUCCESS);
}
