/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 19:10:20 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/09/13 15:49:36 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	shell_pwd(t_shell *cmd)
{
	ft_putstr_fd(cmd->_pwd, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}
