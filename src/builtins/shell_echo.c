/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:55:47 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/09/18 01:06:17 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_single_hyphen_n(char *s)
{
	int	i;

	i = 0;
	if (s[0] != '-' || s[1] != 'n')
		return (false);
	i = 2;
	while (*(s + i))
	{
		if (*(s + i) != 'n')
			return (false);
		i++;
	}
	return (true);
}

void	shell_echo(t_shell *cmd)
{
	char	**s;
	int		i;
	bool	shell_test;

	shell_test = true;
	s = cmd->cmnd;
	if (is_single_hyphen_n(s[1]))
		shell_test = false;
	else
	{
		ft_putstr_fd(s[1], STDOUT_FILENO);
		if (s[2] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	i = 2;
	while (s[i] != NULL)
	{
		ft_putstr_fd(s[i], STDOUT_FILENO);
		if (s[i + 1] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (shell_test)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
