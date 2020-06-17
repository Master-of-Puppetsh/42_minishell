/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 14:55:31 by hjeon             #+#    #+#             */
/*   Updated: 2020/06/17 15:33:57 by hjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"
#include "../../include/minishell.h"

int		ft_export(char *str) //str ex) path=123/asb/23
{
	int		idx;
	char	*name;
	int		cur_size;

	if ((name = get_name(str)) == ERROR)
		return (ERROR);
	idx = find_env_index(name);
	if (idx != ERROR)
	{
		if((cur_size = expand_size(__environ)) == ERROR)
		{
			free(name);
			return (ERROR);
		}
		insert_string(__environ, cur_size, str);
	}
	else
	{
		free(__environ[idx]);
		insert_string(__environ, idx, str);
	}
	free(name);
	return (SUCCESS);
}
