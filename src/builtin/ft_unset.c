/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 15:29:37 by hjeon             #+#    #+#             */
/*   Updated: 2020/06/18 15:31:02 by hjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"
#include "../../include/minishell.h"

int		ft_unset(char *target, char *envp[])
{
	int		i;
	char	*name;
	char	*last_str;

	i = -1;
	while (envp[++i])
	{
		if (!(name = get_name(envp[i])))
			return (ERROR);
		if (!ft_strncmp(name, target, ft_strlen(name)))
		{
			last_str = pop_string(envp);
			envp[i] = last_str;
		}
	}
	return (SUCCESS);
}
