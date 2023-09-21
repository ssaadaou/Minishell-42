/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 22:45:31 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/09/21 03:48:03 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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
	int		i;
	char	*new_add;
	char	*new_str;

	i = 0;
	if (sh_cmnd[search_plus(sh_cmnd, '=')] == '\"')
		remove_quotes(sh_cmnd, '\"');
	if (sh_cmnd[search_plus(sh_cmnd, '=')] == '\'')
		remove_quotes(sh_cmnd, '\'');
	new_add = substring_before_equal(sh_cmnd);
	while (shell_m->str[i])
	{
		new_str = substring_before_equal(shell_m->str[i]);
		if (!ft_strcmp(new_str, new_add))
		{
			free((char *)shell_m->str[i]);
			free(new_str);
			shell_m->str[i] = ft_strdup(sh_cmnd);
			return (free(new_add), 1);
		}
		free(new_str);
		i++;
	}
	free(new_add);
	return (0);
}

int	find_command_exist_plus(char **s, char *sh_cmnd)
{
	int		i;
	char	*new_add;
	char	*new_str;

	i = 0;
	if (sh_cmnd[search_plus(sh_cmnd, '=')] == '\"')
		remove_quotes(sh_cmnd, '\"');
	if (sh_cmnd[search_plus(sh_cmnd, '=')] == '\'')
		remove_quotes(sh_cmnd, '\'');
	new_add = substring_before_equal(sh_cmnd);
	while (s[i] != NULL)
	{
		new_str = substring_before_equal(s[i]);
		if (!ft_strcmp(new_str, new_add))
			return (free(new_str), free(new_add), 1);
		else
			i++;
		free(new_str);
	}
	free(new_add);
	return (0);
}

void	if_qoute_exit(t_shell *shell, char *s)
{
	char	**tmp;

	if (!check_char(shell, s) && !find_command(shell, s))
	{
		if (s)
		{
			tmp = add_var_export(shell->str, s);
			freesplit(shell->str, 0);
			shell->str = tmp;
		}
	}
}

char	*remove_first_plus(char *str)
{
	char	*pos;
	size_t	len;
	char	*s;

	pos = ft_strchr(str, '+');
	if (!pos)
		return (ft_strdup(str));
	len = ft_strlen(str) - 1;
	s = (char *)malloc(len + 1);
	if (!s)
		return (NULL);
	ft_strncpy(s, str, pos - str);
	ft_strcpy(s + (pos - str), pos + 1);
	return (s);
}

void	test_export(t_shell *shell_m, int i)
{
	char	**tmp;
	char	*str;
	char	*s;
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
	else if (search_plus(new_s, '+') && check_plus_equal(shell_m, new_s) \
	&& find_command_exist_plus(shell_m->str, new_s))
	{
		tmp = add_if_plus_exit(shell_m->str, shell_m->cmnd[i]);
		freesplit(shell_m->str, 0);
		shell_m->str = tmp;
	}
	else
	{
		s = remove_first_plus(shell_m->cmnd[i]);
		str = new_string(s);
		if_qoute_exit(shell_m, str);
		free(str);
		free(s);
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
