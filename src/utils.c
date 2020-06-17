/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 18:21:27 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/17 15:36:16 by hjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			get_name(char *str)
{
	return (SUCCESS);
}

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
