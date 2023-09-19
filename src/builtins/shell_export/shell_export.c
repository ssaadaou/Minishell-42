/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 22:45:31 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/09/19 18:07:57 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	**loop_add_var(char **arr, char **rtn, const char *str)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		if (arr[i + 1] == NULL)
		{
			rtn[i] = ft_strdup(str);
			rtn[i + 1] = ft_strdup(arr[i]);
		}
		else
			rtn[i] = ft_strdup(arr[i]);
		if (rtn[i] == NULL)
		{
			freesplit(rtn, 0);
			return (rtn);
		}
		i++;
	}
	return (rtn);
}

char	**add_var_export(char **shell, char *str)
{
	char	**s;
	int		len;

	if (str[search_plus(str, '=')] == '\"')
		remove_quotes(str, '\"');
	if (str[search_plus(str, '=')] == '\'')
		remove_quotes(str, '\'');
	len = set_size_arg(shell);
	s = (char **)ft_calloc(sizeof(char *), (len + 2));
	if (!s)
		return (NULL);
	loop_add_var(shell, s, str);
	return (s);
}

int	find_command(t_shell *shell_m, char *sh_cmnd)
{
	char	**s;
	int		i;

	i = 0;
	s = shell_m->str;
	if (sh_cmnd[search_plus(sh_cmnd, '=')] == '\"')
		remove_quotes(sh_cmnd, '\"');
	if (sh_cmnd[search_plus(sh_cmnd, '=')] == '\'')
		remove_quotes(sh_cmnd, '\'');
	while (s[i])
	{
		if (!ft_strncmp(s[i], sh_cmnd, find_first_equal_or_length(s[i])))
		{
			free(s[i]);
			s[i] = ft_strdup(sh_cmnd);
			return (1);
		}
		i++;
	}
	free(s[i]);
	return (0);
}

void	test_export(t_shell *shell_m, int i)
{
	char	**tmp;
	char	*new_s;

	new_s = remove_double_quotes(shell_m->cmnd[i]);
	if (!search_plus(new_s, '=') && !check_command_export(shell_m, new_s))
	{
		if (check_input(new_s))
			export_unset_err(shell_m->cmnd[0], new_s);
		else
		{
			tmp = add_var_export(shell_m->str, new_s);
			freesplit(shell_m->str, 0);
			shell_m->str = tmp;
		}
	}
	else if (!check_char(shell_m, shell_m->cmnd[i]) && !find_command(shell_m, \
	shell_m->cmnd[i]))
	{
		if (shell_m->cmnd[i])
		{
			tmp = add_var_export(shell_m->str, shell_m->cmnd[i]);
			freesplit(shell_m->str, 0);
			shell_m->str = tmp;
		}
	}
}

void	shell_export(t_shell *sh)
{
	int		i;
	char	**s;

	i = 1;
	s = sh->cmnd;
	if (!s[1])
		shell_env(sh);
	else
	{
		while (s[i])
		{
			test_export(sh, i);
			i++;
		}
	}
}
