/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 15:29:37 by hjeon             #+#    #+#             */
/*   Updated: 2020/06/17 15:43:15 by hjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"
#include "../../include/minishell.h"

int		ft_unset(char *target)
{
	int		i;
	char	*name;
	char	*last_str;

	i = -1;
	while (__environ[++i])
	{
		if ((name = get_name(__environ[i])) == ERROR)
			return (ERROR);
		if (!ft_strncmp(name, target, ft_strlen(name)))
		{
			free(__environ[i]);
			last_str = pop_string(__environ);
			__environ[i] = last_str;
		}
	}
}
