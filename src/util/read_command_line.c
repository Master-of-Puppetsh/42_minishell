/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 03:32:38 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/26 17:27:37 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

static char		*cat_buff(char c, char *buff)
{
	char	*result;
	int		buff_len;
	int		i;

	buff_len = ft_strlen(buff);
	if (!(result = malloc(sizeof(char) * (buff_len + 2))))
		return (NULL);
	i = 0;
	while (i < buff_len)
	{
		result[i] = buff[i];
		i++;
	}
	result[i++] = c;
	result[i] = '\0';
	free(buff);
	return (result);
}


char	*read_command_line(void)
{
	int		read_bytes;
	char	*buff;
	char	c;

	if (!(buff = ft_strdup("")))
		exit(0); // TODO
	while (1)
	{
		read_bytes = read(STDIN_FILENO, &c, 1);
		// write(STDOUT_FILENO, ft_itoa(c), 3);
		// write(STDOUT_FILENO, "\n", 1);
		if (read_bytes == 0)
		{
			if (*buff)
				continue ;
			else
				exit(0); // 확정은아님
		}
		if (c == '\n')
			return (buff);
		else if (read_bytes != 0)
			buff = cat_buff(c, buff);
	}
}
