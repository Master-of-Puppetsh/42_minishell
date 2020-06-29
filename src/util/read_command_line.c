/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 03:32:38 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/29 16:26:16 by hjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

char		*cat_buff(char c, char *buff)
{
	char	*result;
	int		buff_len;
	int		i;

	buff_len = ft_strlen(buff);
	if (!(result = ft_calloc(sizeof(char), (buff_len + 2))))
		return (NULL);
	i = 0;
	while (i < buff_len)
	{
		result[i] = buff[i];
		i++;
	}
	result[i] = c;
	free(buff);
	return (result);
}

char		*read_command_line(int status)
{
	int		read_bytes;
	char	*buff;
	char	c;

	if (!(buff = ft_strdup("")))
		exit(CMD_ERR);
	while (1)
	{
		read_bytes = read(STDIN_FILENO, &c, 1);
		if (read_bytes == 0)
		{
			if (*buff)
				continue ;
			else
				exit(status);
		}
		if (c == '\n')
			return (buff);
		else if (read_bytes != 0)
			buff = cat_buff(c, buff);
	}
}
