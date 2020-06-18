/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 03:32:38 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/12 18:02:19 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "get_next_line.h"

static char		*cat_buff(char *str, char *buff, ssize_t buff_idx)
{
	char	*result;
	ssize_t	str_len;
	ssize_t	i;

	str_len = ft_strlen(str);
	if (!(result = malloc(sizeof(char) * (str_len + 1 + buff_idx))))
		return (NULL);
	i = 0;
	while (i < str_len)
	{
		result[i] = str[i];
		i++;
	}
	while (i < str_len + buff_idx)
	{
		result[i] = buff[i - str_len];
		i++;
	}
	result[i] = '\0';
	free(str);
	return (result);
}

static ssize_t	smart_read(int fd, char *buff, size_t bytes)
{
	ssize_t	new_line_idx;
	ssize_t	read_bytes;

	if ((new_line_idx = ft_stridx(buff, '\n')) != -1)
	{
		return (new_line_idx);
	}
	if ((read_bytes = read(fd, buff, bytes)) == -1)
		return (-1);
	buff[read_bytes] = '\0';
	if ((new_line_idx = ft_stridx(buff, '\n')) != -1)
	{
		return (new_line_idx);
	}
	return (read_bytes);
}

static void		ltrim_buff(char *buff, ssize_t new_line_idx)
{
	ssize_t	i;

	i = 0;
	while (buff[new_line_idx + i + 1] != '\0')
	{
		buff[i] = buff[new_line_idx + i + 1];
		i++;
	}
	buff[i] = '\0';
}

static int		check_buff_new_line(char *buff, char **line)
{
	int		buff_idx;

	if ((buff_idx = ft_stridx(buff, '\n')) != -1)
	{
		if (!(*line = cat_buff(*line, buff, buff_idx)))
			return (-1);
		ltrim_buff(buff, buff_idx);
		return (1);
	}
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char		buff[BUFFER_SIZE + 1];
	ssize_t			buff_idx;
	int				check_result;

	if (line == NULL || BUFFER_SIZE <= 0 || !(*line = malloc(sizeof(char))))
		return (-1);
	**line = '\0';
	check_result = check_buff_new_line(buff, line);
	if (check_result == 1 || check_result == -1)
		return (check_result);
	if (!(*line = cat_buff(*line, buff, ft_strlen(buff))))
		return (-1);
	while ((buff_idx = smart_read(fd, buff, BUFFER_SIZE)) >= 0)
	{
		if (!(*line = cat_buff(*line, buff, buff_idx)))
			return (-1);
		if (buff[buff_idx] == '\n')
		{
			ltrim_buff(buff, buff_idx);
			return (1);
		}
		if (buff[buff_idx] == '\0' && buff_idx == 0)
			return (0);
	}
	return (-1);
}
