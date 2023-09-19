/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:50:15 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/09/18 01:09:58 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	shell_exit(t_shell *cmd)
{
	int	numb_exit;

	if (!cmd->cmnd[1])
	{
		ft_putstr_fd("\033[1;32mexit\n\033[0m", STDERR_FILENO);
		exit(STDIN_FILENO);
	}
	if (is_all_digit(cmd->cmnd[1]) && cmd->cmnd[2])
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
	else if (is_all_digit(cmd->cmnd[1]))
	{
		ft_putstr_fd("\033[1;34mexit\n\033[0m", STDERR_FILENO);
		numb_exit = atoi_exit(cmd->cmnd[1]);
		exit(numb_exit);
	}
	else
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd->cmnd[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		numb_exit = 255;
		exit(numb_exit);
	}
}
