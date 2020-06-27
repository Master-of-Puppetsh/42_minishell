/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 20:16:26 by hjeon             #+#    #+#             */
/*   Updated: 2020/06/18 21:2317 by hjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/libft.h"

char	*replace_text(char *dest, int start, int length, char *src)
{
	char	*result;
	int		total_len;

	if (dest == NULL)
		exit_with_err_msg(ERRMSG_MALLOC, 1);
	total_len = ft_strlen(src) + ft_strlen(dest) - length + 1;
	if (!(result = ft_calloc(total_len, sizeof(char))))
		exit_with_err_msg(ERRMSG_MALLOC, 1);
	ft_strlcat(result, dest, start);
	ft_strlcat(result, src, start + ft_strlen(src));
	ft_strlcat(result, dest + start + length, total_len);
	free(dest);
	return (result);
}

int		is_in_charset(char c, char *str)
{
	while (*str != '\0')
	{
		if (c == *str)
			return (1);
		str++;
	}
	return (0);
}

void	replace_env(char **arg, char **envp, int status)
{
	int		i;
	int		j;
	char	*name;
	char	*value;
	char	quote;

	i = -1;
	quote = 0;
	while (*(*arg + ++i) != '\0')
	{
		quote = check_quote((*arg + i), quote);
		if (*(*arg + i) == '$' && *(*arg + i + 1) != '\0' && (quote == '\"' || quote == 0))
		{
			if (*(*arg + ++i) == '?')
			{
				if (!(value = ft_itoa(status)))
					exit_with_err_msg(ERRMSG_MALLOC, CMD_ERR);
				*arg = replace_text(*arg, i, 1, value);
				i += ft_strlen(value) - 2;
				free(value);
				continue ;
			}
			j = 0;
			while (!(*(*arg + i + j) == '\0') && !is_in_charset(*(*arg + i + j), "\'\"$ "))
				j++;
			if (!(name = ft_substr((*arg + i), 0, j)))
				exit_with_err_msg(ERRMSG_MALLOC, CMD_ERR);
			value = ft_getenv(name, envp);
			free(name);
			*arg = replace_text(*arg, i, j, value);
			i += ft_strlen(value) - 2;
			printf("idx: %d\n", i);
		}
		if (quote == 1)
			quote = 0;
	}
}

void		remove_quotes(char *str)
{
	char	quote;

	quote = 0;
	while (*str != '\0')
	{
		quote = check_quote(str, quote);
		if ((*str == '\'' || *str == '\"') && (quote == *str || quote == 1))
		{
			ft_memmove(str, str + 1, ft_strlen(str + 1) + 1);
			str--;
		}
		if (quote == 1)
			quote = 0;
		str++;
	}
}

char		**parse_command(char *command, char **envp, int status)
{
	char	**argv;
	int		i;

	if (!(argv = split_command(command, ' '))) // TODO: white space
		exit_with_err_msg(ERRMSG_MALLOC, 1);
	i = 0;
	while (*(argv + i) != NULL)
	{
		replace_env(argv + i, envp, status);
		remove_quotes(*(argv + i));
		i++;
	}
	return (argv);
}

void		execute_builtin(char **argv, char ***envp, int *status)
{
	if (ft_strncmp(argv[0], "echo", 5) == 0)
		*status = ft_echo(argv);
	else if (ft_strncmp(argv[0], "cd", 3) == 0)
		*status = ft_cd(argv, *envp);
	else if (ft_strncmp(argv[0], "pwd", 4) == 0)
		*status = ft_pwd();
	else if (ft_strncmp(argv[0], "export", 7) == 0)
		*status = ft_export(argv, envp);
	else if (ft_strncmp(argv[0], "unset", 6) == 0)
		*status = ft_unset(argv, envp);
	else if (ft_strncmp(argv[0], "env", 4) == 0)
		*status = ft_env(*envp);
	else if (ft_strncmp(argv[0], "exit", 5) == 0)
		*status = ft_exit(argv, *status);
	else
		*status = CMD_NOT_FOUND;
}
