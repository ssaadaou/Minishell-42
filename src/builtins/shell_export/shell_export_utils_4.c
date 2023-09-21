/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_export_utils_4.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:12:31 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/09/21 03:51:30 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	check_plus_equal(t_shell *cmd, char *s)
{
	int		i;
	int		len;
	size_t	length;
	char	*plus_pos;

	if (ft_isdigit(s[0]))
		return (export_unset_err(cmd->cmnd[0], s));
	plus_pos = ft_strstr(s, "+=");
	if (!plus_pos)
		return (0);
	length = plus_pos - s;
	if (length > 0 && (s[length - 1] == '\'' || s[length - 1] == '\"'))
		len = length -1;
	else
		len = length;
	i = 0;
	while (i < len)
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (export_unset_err(cmd->cmnd[0], s));
		i++;
	}
	return (1);
}

char	*extract_before_equal(char *s)
{
	char	*pos;
	size_t	len;
	char	*new_s;

	pos = ft_strchr(s, '=');
	if (!pos)
		return (ft_strdup(s));
	len = pos - s;
	new_s = (char *)malloc((len + 1) * sizeof(char));
	if (!new_s)
		return (NULL);
	ft_strncpy(new_s, s, len);
	new_s[len] = '\0';
	return (new_s);
}

char	*extract_after_equal(char *s)
{
	int	pos;

	pos = find_first_equal_or_length(s) + 1;
	return (ft_strdup(s + pos));
}

char	*extract_before_plus(char *s)
{
	char	*pos;
	size_t	len;
	char	*new_s;

	pos = ft_strchr(s, '+');
	if (!pos)
		return (ft_strdup(s));
	len = pos - s;
	new_s = (char *)malloc((len + 1) * sizeof(char));
	if (!new_s)
		return (NULL);
	ft_strncpy(new_s, s, len);
	new_s[len] = '\0';
	return (new_s);
}

// void	check_1(char **s, char *s_add, int j, int i, char **new_s)
// {
	
// }

char	**add_if_plus_exit(char **s, char *s_add)
{
	int		i;
	int		j;
	char	**new_s;
	int		len;

	len = set_size_arg(s);
	new_s = (char **)ft_calloc(sizeof(char *), len + 1);
	if (!new_s)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] != NULL)
	{
		char	*s1;
		char	*s2;

		s1 = extract_before_equal(s[i]);
		s2 = extract_before_plus(s_add);
		if (!ft_strcmp(s1, s2) && s1 && s2)
		{
			char *s3 = extract_after_equal(s_add);
			if (!search_plus(s[i], '='))
				s[i] = ft_strjoin(s[i], "=");
			new_s[j] = ft_strjoin(s[i], s3);
			free(s3);
		}
		else
			new_s[j] = ft_strdup(s[i]);
		free(s1);
		free(s2);
		i++;
		j++;
	}
	new_s[j] = NULL;
	return (new_s);
}
