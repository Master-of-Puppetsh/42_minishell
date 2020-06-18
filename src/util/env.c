/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 16:21:25 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/12 18:07:09 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/minishell.h"

char	**init_env(char *envp[])
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
