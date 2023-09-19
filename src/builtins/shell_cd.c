/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 19:54:01 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/09/13 23:32:23 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_way(char *cmd, t_shell *cm)
{
	char	*path_test;
	int		ret_path;
	int		len;

	path_test = find_path(cm, cmd);
	ret_path = chdir(path_test);
	len = ft_strlen(cmd) - 1;
	free(path_test);
	if (ret_path != 0)
	{
		cmd = ft_substr(cmd, 0, len);
		ft_putstr_fd(cmd, STDERR_FILENO);
		free(cmd);
		ft_putstr_fd(" not set\n", STDERR_FILENO);
	}
	return (ret_path);
}

void	add_up_to_env(t_shell *m_shell)
{
	int		i;
	char	*path;
	char	**s;

	s = m_shell->str;
	i = 0;
	while (s[i])
	{
		if (!ft_strncmp(s[i], "PWD=", 4))
		{
			path = ft_strjoin("PWD=", m_shell->_pwd);
			free(s[i]);
			s[i] = path;
		}
		else if (!ft_strncmp(s[i], "OLDPWD=", 7) && m_shell->_oldpwd)
		{
			path = ft_strjoin("OLDPWD=", m_shell->_oldpwd);
			free(s[i]);
			s[i] = path;
		}
		i++;
	}
}

void	change_path(t_shell *cmd)
{
	char	*new_pwd;
	char	*err;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		err = ft_strjoin("cd: error retrieving current directory: getcwd:\
			cannot access parent directories: ", strerror(errno));
		ft_putstr_fd(err, STDERR_FILENO);
		free(err);
		return ;
	}
	free(cmd->_oldpwd);
	cmd->_oldpwd = cmd->_pwd;
	cmd->_pwd = new_pwd;
}

void	check_cd_arg(t_shell *cmd)
{
	char	**s;

	s = cmd->cmnd;
	if (s && s[1] && s[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return ;
	}
}

void	shell_cd(t_shell *shell_m)
{
	int		ret;
	char	**s;

	s = shell_m->cmnd;
	check_cd_arg(shell_m);
	if (!s[1] || !ft_strncmp(s[1], "~", 1) || !ft_strncmp(s[1], "--", 2)) 
		ret = check_way("HOME=", shell_m);
	else if (!ft_strncmp(s[1], "-", 1))
		ret = check_way("OLDPWD=", shell_m);
	else
	{
		ret = chdir(s[1]);
		if (ret == -1)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(s[1], STDERR_FILENO);
			perror(" ");
		}
	}
	if (ret != 0)
		return ;
	change_path(shell_m);
	add_up_to_env(shell_m);
	if (s[1] && !ft_strcmp(s[1], "-"))
		printf("%s\n", shell_m->_pwd);
}
