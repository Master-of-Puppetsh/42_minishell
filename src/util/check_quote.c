/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 21:00:33 by hjeon             #+#    #+#             */
/*   Updated: 2020/06/30 21:01:09 by hjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		check_quote(char *str, char quote, int idx)
{
	if (is_escape(idx, quote, str) == 1)
		return (quote);
	if ((str[idx] == '\'' || str[idx] == '\"') && ((quote == 0)))
		quote = str[idx];
	else if ((str[idx] == '\'' || str[idx] == '\"') && (quote == str[idx]))
		quote = 1;
	return (quote);
}

char		check_quote_passing_escape(char *str, char quote, int idx)
{
	if ((str[idx] == '\'' || str[idx] == '\"') && ((quote == 0)))
		quote = str[idx];
	else if ((str[idx] == '\'' || str[idx] == '\"') && (quote == str[idx]))
		quote = 1;
	return (quote);
}
