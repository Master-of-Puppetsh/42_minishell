/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 01:57:58 by hyekim            #+#    #+#             */
/*   Updated: 2020/07/01 20:16:32 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

int		ft_cd(char **argv, char *envp[])
{
	int		result;
	char	*home;
	char	*path;
	int		total_len;

	home = ft_getenv("HOME", envp);
	if (argv[1] == NULL)
		result = chdir(home);
	else if (argv[1][0] == '~' && (argv[1][1] == '\0' || argv[1][1] == '/'))
	{
		total_len = ft_strlen(home) + ft_strlen(argv[1]);
		if (!(path = ft_calloc(total_len, sizeof(char))))
			exit_with_err_msg(ERRMSG_MALLOC, 1);
		ft_strlcat(path, home, ft_strlen(home) + 1);
		ft_strlcat(path, argv[1] + 1, total_len);
		result = chdir(path);
		free(path);
	}
	else
		result = chdir(argv[1]);
	if (result == ERROR)
		print_error("cd", argv[1], NULL);
	return (result * -1);
}
