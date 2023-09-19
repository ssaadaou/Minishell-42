/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:04:17 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/09/17 22:58:20 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_minishell(t_shell *shell)
{
	free(shell->path);
	free(shell->_oldpwd);
	free(shell->_pwd);
	freesplit(shell->cmnd, 0);
}

void	search_p_o_p(t_shell *cmd)
{
	char	**s;
	int		i;

	s = cmd->str;
	i = 0;
	while (s[i])
	{
		if (!ft_strncmp(s[i], "PWD=", 4))
			cmd->_pwd = ft_substr(s[i], 4, ft_strlen(s[i]) - 4);
		if (!ft_strncmp(s[i], "OLDPWD=", 7))
			cmd->_oldpwd = ft_substr(s[i], 7, ft_strlen(s[i]) - 7);
		if (!ft_strncmp(s[i], "PATH=", 5))
			cmd->path = ft_substr(s[i], 5, ft_strlen(s[i]) - 5);
		i++;
	}
	if (!cmd->_pwd)
		cmd->path = ft_strdup("");
}

char	*find_path(t_shell *mini_s, char *find)
{
	int		i;
	int		len;
	char	**s;
	char	*path;

	s = mini_s->str;
	len = ft_strlen(find);
	path = NULL;
	i = 0;
	while (s[i])
	{
		if (!ft_strncmp(s[i], find, len))
			path = ft_substr(s[i], len, ft_strlen(s[i]) - len);
		i++;
	}
	return (path);
}
