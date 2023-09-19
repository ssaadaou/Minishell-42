/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:48:50 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/09/20 00:02:50 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	check_cmnd_unset(char *s)
{
	int	i;

	i = 0;
	if (!ft_isalpha(*s) && *s != '_')
	{
		i++;
		return (false);
	}
	while (*(s + i))
	{
		if (!ft_isalnum(*(s + i)) && *(s + i) != '_')
			return (false);
		i++;
	}
	return (true);
}

bool	check_syntax_cmd(char *env, char *cmnd)
{
	char	*sub_cmnd;

	if (ft_strchr(env, '='))
		sub_cmnd = ft_substr(env, 0, search_plus(env, '=') - 1);
	else
		sub_cmnd = ft_strdup(env);
	if (!ft_strcmp(cmnd, sub_cmnd))
		return (free(sub_cmnd), false);
	free(sub_cmnd);
	return (true);
}

char	**loop_add_env(char *str, char **env, char **cmd)
{
	char	*new_s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env[i] != NULL)
	{
		new_s = substring_before_equal(env[i]);
		if (strcmp(new_s, str))
		{
			cmd[j] = strdup(env[i]);
			if (!cmd[j])
				return (freesplit(cmd, 0), cmd);
			j++;
		}
		free(new_s);
		i++;
	}
	return (cmd);
}

char	**del_var(char *cmd, char **env)
{
	char	**new_env;
	int		len;

	len = set_size_arg(env);
	new_env = ft_calloc(len + 1, sizeof(char *));
	if (!new_env)
		return (new_env);
	new_env = loop_add_env(cmd, env, new_env);
	return (new_env);
}

void	shell_unset(t_shell *sh_m)
{
	char	**tmp;
	char	*new_cmd;
	int		i;

	i = 1;
	while (sh_m->cmnd[i])
	{
		new_cmd = remove_double_quotes(sh_m->cmnd[i]);
		if (!check_cmnd_unset(new_cmd))
			export_unset_err(sh_m->cmnd[0], new_cmd);
		else if (!ft_strcmp("PWD", new_cmd))
			return ;
		else
		{
			tmp = del_var(new_cmd, sh_m->str);
			freesplit(sh_m->str, 0);
			sh_m->str = tmp;
		}
		i++;
	}
}
