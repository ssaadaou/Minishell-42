/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:55:47 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/09/21 20:05:27 by ylamsiah         ###   ########.fr       */
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
    int		i;
    char	**s;
    bool	shell_test;

	i = 1;
	s = cmd->cmnd;
	shell_test = true;
    while (s[i] && is_single_hyphen_n(s[i]))
	{
		shell_test = false;
        i++;
    }
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
