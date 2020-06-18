/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 14:55:31 by hjeon             #+#    #+#             */
/*   Updated: 2020/06/18 19:22:44 by hjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"
#include "../../include/minishell.h"

int		ft_export(char *str, char *envp[]) //str ex) path=123/asb/23
{
	int		idx;
	char	*name;
	int		cur_size;

	if (!(name = get_name(str)))
		return (ERROR);
	idx = find_env_index(name, envp);
	if (idx == ERROR)
	{
		if((cur_size = expand_envp(&envp)) == ERROR)
		{
			free(name);
			return (ERROR);
		}
		insert_string(envp, cur_size, str);
	}
	else
	{
		free(envp[idx]);
		insert_string(envp, idx, str);
	}
	free(name);
	return (SUCCESS);
}
