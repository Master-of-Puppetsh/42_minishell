/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 16:21:25 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/26 17:57:55 by hjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_paths(char *envp[])
{
	char	**paths;
	char	*new_path;
	int		i;

	i = 0;
	while (*envp != NULL)
	{
		if (!ft_strncmp(*envp, "PATH", 4))
		{
			if (!(paths = ft_split(*(envp) + 5, ':')))
				return (NULL);
			while (*(paths + i))
			{
				if (!(new_path = ft_strjoin(*(paths + i), "/")))
					return (NULL);
				free(*(paths + i));
				*(paths + i) = new_path;
				i++;
			}
			return (paths);
		}
		envp++;
	}
	return (NULL);
}
