/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 16:21:25 by hyekim            #+#    #+#             */
/*   Updated: 2020/07/02 15:37:36 by hjeon            ###   ########.fr       */
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

int		is_in_charset(char c, char *str)
{
	while (*str != '\0')
	{
		if (c == *str)
			return (1);
		str++;
	}
	return (0);
}

int		replace_question_to_status(int status, int i, char **arg)
{
	char	*value;

	if (!(value = ft_itoa(status)))
		exit_with_err_msg(ERRMSG_MALLOC, CMD_ERR);
	*arg = replace_text(*arg, i, 1, value);
	free(value);
	return (ft_strlen(value) - 2);
}

int		do_replace_env(int i, char **arg, char **envp)
{
	int		j;
	char	*name;
	char	*value;

	j = 0;
	while (!(*(*arg + i + j) == '\0')
			&& !is_in_charset(*(*arg + i + j), "\'\"$ !#%*+,-./[]^`{}~"))
		j++;
	if (!(name = ft_substr((*arg + i), 0, j)))
		exit_with_err_msg(ERRMSG_MALLOC, CMD_ERR);
	value = ft_getenv(name, envp);
	free(name);
	*arg = replace_text(*arg, i, j, value);
	return (ft_strlen(value) - 2);
}

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
