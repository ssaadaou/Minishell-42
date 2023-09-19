/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_export_utils_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:43:00 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/09/19 22:50:06 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*substring_before_equal(char *str)
{
	char	*equal_sign;
	size_t	length;
	char	*result;

	result = NULL;
	equal_sign = ft_strchr(str, '=');
	if (equal_sign != NULL)
	{
		length = equal_sign - str;
		result = (char *)malloc(length + 1);
		if (result != NULL)
		{
			ft_strncpy(result, str, length);
			result[length] = '\0';
		}
	}
	else
	{
		result = ft_strdup(str);
		free(str);
	}
	return (result);
}

int	findsubstring(char *str)
{
	int	length;
	int	i;

	i = 0;
	length = ft_strlen(str);
	while (i < length)
	{
		if ((str[i] == '\"' && str[i + 1] == '=') \
		|| (str[i] == '\'' && str[i + 1] == '='))
			return (i);
		else
			i++;
	}
	return (-1);
}

char	*new_string(char *s)
{
	int		i;
	int		j;
	int		len;
	char	*s_new;

	s_new = (char *)malloc((strlen(s) + 1) * sizeof(char));
	if (!s_new)
		return (NULL);
	i = 0;
	j = 0;
	len = findsubstring(s);
	while (*(s + i))
	{
		if (i == len)
		{
			i++;
			*(s_new + j) = *(s + i);
		}
		else
			*(s_new + j) = *(s + i);
		j++;
		i++;
	}
	*(s_new + j) = '\0';
	return (s_new);
}

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
