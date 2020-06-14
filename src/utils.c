/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 18:21:27 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/14 15:06:51 by hyekim           ###   ########.fr       */
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
