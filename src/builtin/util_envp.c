/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 14:23:02 by hjeon             #+#    #+#             */
/*   Updated: 2020/06/18 15:25:14 by hjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/libft.h"

char	*get_name(char *str)
{
	int		i;
	char	*ret;

	i = -1;
	while (*(str + ++i))
	{
		if (*(str + i) == '=')
		{
			if (!(ret = ft_substr(str, 0, i)))
				return (NULL);
			return (ret);
		}
	}
	return (NULL);
}

int		find_env_index(char *target, char *envp[])
{
	int		i;
	char	*name;

	i = -1;
	while (*(envp + ++i))
	{
		if (!(name = get_name(*(envp + i))))
			return (ERROR);
		if (ft_strncmp(target, name, ft_strlen(name)) == 0)
		{
			free(name);
			return (i);
		}
		free(name);
	}
	return (FAIL);
}

int		expand_envp(char	***envp)
{
	char	**expanded_envp;
	int		i;

	i = -1;
	while (*(*envp + ++i))
		;
	if (!(expanded_envp = ft_calloc(sizeof(char *), i + 2)))
		return (0);
	i = -1;
	while (*(*envp + ++i))
		*(expanded_envp + i) = *(*envp + i);
	// free (*envp); is not malloced?
	*envp = expanded_envp;
	return (i + 1);
}

int		insert_string(char **envp, int	idx, char *str)
{
	if (!(envp[idx] = ft_strdup(str)))
		return (ERROR);
	return (SUCCESS);
}

char	*pop_string(char **envp)
{
	int		i;
	char	*last_string;

	i = -1;
	while (*(envp + ++i))
		;
	last_string = *(envp + i - 1);
	*(envp + i - 1) = NULL;
	return (last_string);
}
