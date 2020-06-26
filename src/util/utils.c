/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 18:21:27 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/26 18:44:19 by hjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		*free_split(char **splitted_str)
{
	int		i;

	i = 0;
	while (*(splitted_str + i))
	{
		free(*(splitted_str + i));
		i++;
	}
	free(splitted_str);
	return (NULL);
}

void		exit_with_err_msg(char *msg, int status)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(status);
}

void	prompt(void)
{
	write(STDERR_FILENO, "$ ", 2);
}
