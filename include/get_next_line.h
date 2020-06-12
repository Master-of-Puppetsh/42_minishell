/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 03:19:45 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/12 17:05:40 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef GET_NEXT_LINE_H
#	define GET_NEXT_LINE_H
#	ifndef BUFFER_SIZE
#	define BUFFER_SIZE 10
#	endif
#	include <unistd.h>
#	include <stdlib.h>
#	include "libft.h"
ssize_t		ft_stridx(char *str, char target);
int			get_next_line(int fd, char **line);

#	endif
