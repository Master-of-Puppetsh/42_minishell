/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_redirection_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 20:57:20 by hjeon             #+#    #+#             */
/*   Updated: 2020/06/28 20:58:54 by hjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

void		reset_std(t_list *list)
{
	t_redirection	*redirection;

	while (list)
	{
		redirection = list->content;
		dup2(redirection->copied_std, redirection->is_stdout);
		close(redirection->fd);
		close(redirection->copied_std);
		list = list->next;
	}
}

int		free_redirection(t_list **begin_list, t_redirection *redirection)
{
	reset_std(*begin_list);
	free(redirection);
	return (ERROR);
}
