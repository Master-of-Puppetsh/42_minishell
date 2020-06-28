/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 16:21:25 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/28 21:24:49 by hjeon            ###   ########.fr       */
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
		if (!ft_strncmp(*envp, "PATH=", 5))
		{
			if (!(paths = ft_split(*(envp) + 5, ':')))
				exit_with_err_msg(ERRMSG_MALLOC, 1);
			while (*(paths + i))
			{
				if (!(new_path = ft_strjoin(*(paths + i), "/")))
					exit_with_err_msg(ERRMSG_MALLOC, 1);
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
