/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_export_utils_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 21:36:06 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/09/19 20:11:48 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	find_first_equal_or_length(char *str)
{
    int length = ft_strlen(str);
    int i;
	
	i = 0;
    while (i < length)
	{
        if (str[i] == '=')
            return (i - 1);
        i++;
    }

    return (length);
}

int	search_plus(char *s, char d_quot)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == d_quot)
		{
			i++;
			return (i);
		}
		i++;
	}
	return (0);
}

bool	check_command_export(t_shell *sh_m, char *cmd)
{
	int		i;
	int		first;
	char	*s;

	i = 0;
	while (sh_m->str[i])
	{
		first = search_plus(sh_m->str[i], '=');
		s = ft_substr(sh_m->str[i], 0, first - 1);
		if (!ft_strcmp(s, cmd))
			return (free(s), true);
		free(s);
		i++;
	}
	return (false);
}

int	export_unset_err(char *cmd, char *s)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (s != NULL)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putchar_fd('\'', STDERR_FILENO);
		ft_putstr_fd(s, STDERR_FILENO);
		ft_putstr_fd("\': is ", STDERR_FILENO);
	}
	ft_putstr_fd("not a valid identifier", STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (EXIT_FAILURE);
}

char	*remove_double_quotes(char *str)
{
	int len;

	len = ft_strlen(str);
	if (len > 0 && str[0] == '"')
	{
		ft_memmove(str, str + 1, len);
		len--;
	}
	if (len > 0 && str[len - 1] == '"') 
		str[len - 1] = '\0';
	return (str);
}
