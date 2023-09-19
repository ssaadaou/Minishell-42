/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:52:51 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/09/19 17:34:54 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_buil(t_shell *msh)
{
	if (!msh->cmnd || !msh->cmnd[0])
		return (false);
	else if (!ft_strcmp(msh->cmnd[0], "exit"))
		return (true);
	else if (!ft_strcmp(msh->cmnd[0], "env"))
		return (true);
	else if (!ft_strcmp(msh->cmnd[0], "cd"))
		return (true);
	else if (!ft_strcmp(msh->cmnd[0], "echo"))
		return (true);
	else if (!ft_strcmp(msh->cmnd[0], "pwd"))
		return (true);
	else if (!ft_strcmp(msh->cmnd[0], "export"))
		return (true);
	else if (!ft_strcmp(msh->cmnd[0], "unset"))
		return (true);
	return (false);
}

void	mini_exec(t_shell *m_sh)
{
	if (is_buil(m_sh))
	{
		if (!ft_strcmp(m_sh->cmnd[0], "exit"))
			shell_exit(m_sh);
		else if (!ft_strcmp(m_sh->cmnd[0], "env"))
			shell_env(m_sh);
		else if (!ft_strcmp(m_sh->cmnd[0], "cd"))
			shell_cd(m_sh);
		else if (!ft_strcmp(m_sh->cmnd[0], "echo"))
			shell_echo(m_sh);
		else if (!ft_strcmp(m_sh->cmnd[0], "pwd"))
			shell_pwd(m_sh);
		else if (!ft_strcmp(m_sh->cmnd[0], "export"))
			shell_export(m_sh);
		else if (!ft_strcmp(m_sh->cmnd[0], "unset"))
			shell_unset(m_sh);
	}
	else
		printf("%s : command not found\n", m_sh->cmnd[0]);
}
