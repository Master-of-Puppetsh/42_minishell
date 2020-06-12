/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 00:28:43 by hyekim            #+#    #+#             */
/*   Updated: 2020/04/04 00:45:41 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char mod;

	if (n == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		mod = -(n % 10) + 48;
		n /= -10;
	}
	else
	{
		mod = n % 10 + 48;
		n /= 10;
	}
	if (n == 0)
	{
		ft_putchar_fd(mod, fd);
		return ;
	}
	ft_putnbr_fd(n, fd);
	ft_putchar_fd(mod, fd);
}
