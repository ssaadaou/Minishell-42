/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:03:42 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/09/09 14:27:20 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

long long int	atoi_exit(const char *str)
{
	long long int	n;
	int				sign;

	n = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		if (n > LLONG_MAX / 10 || (n == LLONG_MAX / 10 \
		&& (*str - '0') > LLONG_MAX % 10))
			return (-1);
		n = n * 10 + (*str - '0');
		str++;
	}
	return (n * sign);
}
