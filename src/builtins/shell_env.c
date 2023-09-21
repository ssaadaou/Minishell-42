/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:58:12 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/09/21 21:23:10 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strd(char *s, t_shell *sh_m)
{
	char	*str;
	int		i;
	int		j;

	str = (char *)ft_calloc(sizeof(char ), (ft_strlen(s) + 3));
	if (!str)
		return (str);
	i = -1;
	j = 0;
	sh_m->test = true;
	while (*(s + ++i))
	{
		if (*(s + i) == '=' && sh_m->test == true)
		{
			*(str + j++) = *(s + i);
			*(str + j++) = '"';
			sh_m->test = false;
		}
		else
			*(str + j++) = *(s + i);
	}
	if (!sh_m->test)
		*(str + j++) = '"';
	*(str + j) = '\0';
	return (str);
}

void check_env_export(char *s, char *cmnd)
{
	if (search_plus(s, '=') && ft_strcmp(cmnd, "export"))
	{
		ft_putstr_fd(s, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	else if (ft_strcmp(cmnd, "env"))
	{
		ft_putstr_fd(s, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}

void	shell_env(t_shell *cmd)
{
	int		i;
	char	*s;
	char	*tmp;
	char	*cmnd;

	i = 0;
	while (cmd->str[i])
	{
		cmnd = cmd->cmnd[0];
		cmd->cp = cmd->str[i];
		if (!ft_strcmp(cmnd, "export"))
		{
			tmp = "declare -x ";
			cmd->cp = ft_strd(cmd->cp, cmd);
		}
		else
			tmp = "";
		s = ft_strjoin(tmp, cmd->cp);
		check_env_export(s, cmnd);
		if (!ft_strcmp(cmnd, "export"))
			free(cmd->cp);
		free(s);
		i++;
	}
}
