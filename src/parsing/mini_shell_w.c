/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell_w.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 22:34:38 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/09/17 22:55:32 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	mini_shell_w(t_shell *cmd)
{
	char	*input;

	signal(SIGINT, SIG_IGN);
	while (1) 
	{
		signal(SIGINT, sig_ctlc);
		input = readline("\033[1;36mminishell\033[34m$ \033[0m");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (input[0])
		{
			add_history(input);
			cmd->cmnd = ft_split(input, ' ');
			search_p_o_p(cmd);
			mini_exec(cmd);
			free_minishell(cmd);
		}
		free(input);
	}
}
