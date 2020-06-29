/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 15:16:43 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/29 16:01:54 by hjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

int		is_numeric_arg(char *arg)
{
	while (*arg != '\0')
	{
		if (ft_isdigit(*arg) == 0)
			return (0);
		arg++;
	}
	return (1);
}

int		ft_exit(char **argv, int status)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	if (!argv[1])
		exit(status);
	if (is_numeric_arg(argv[1]))
	{
		if (argv[1] && argv[2])
		{
			print_error("exit", NULL, "too many arguments");
			return (CMD_ERR);
		}
		exit(ft_atoi(argv[1]));
	}
	print_error("exit", argv[1], "numeric argument required");
	exit(255);
	return (SUCCESS);
}
