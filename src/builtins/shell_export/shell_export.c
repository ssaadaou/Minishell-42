/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 22:45:31 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/09/19 20:35:18 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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

char *substring_before_equal(const char *str) {
    // Find the position of the first '=' character in the string
    const char *equal_sign = strchr(str, '=');

    if (equal_sign != NULL) {
        // Calculate the length of the substring before '='
        size_t length = equal_sign - str;

        // Allocate memory for the result buffer
        char *result = (char *)malloc(length + 1); // +1 for null-termination

        if (result != NULL) {
            // Copy the substring before '=' into the result buffer
            strncpy(result, str, length);
            result[length] = '\0'; // Null-terminate the result
        }

        return result;
    } else {
        // '=' was not found in the string, so return a copy of the input string
        return strdup(str);
    }
}

int	find_command(t_shell *shell_m, char *sh_cmnd)
{
	char	**s;
	int		i;

	i = 0;
	s = shell_m->str;
	if (sh_cmnd[search_plus(sh_cmnd, '=')] == '\"')
		remove_quotes(sh_cmnd, '\"');
	if (sh_cmnd[search_plus(sh_cmnd, '=')] == '\'')
		remove_quotes(sh_cmnd, '\'');
	char *new_add = substring_before_equal(sh_cmnd);
	while (s[i])
	{
		char *new_str = substring_before_equal(s[i]);
		if (!ft_strcmp(new_str, new_add))
		{
			free(s[i]);
			s[i] = ft_strdup(sh_cmnd);
			return (1);
		}
		i++;
	}
	free(s[i]);
	return (0);
}

int findSubstring(const char *str) {
    int length = strlen(str);

    int i = 0;
    while ( i < length) {
        if ((str[i] == '\"' && str[i + 1] == '=') ||
            (str[i] == '\'' && str[i + 1] == '=')) {
            return (i);
        }
        else
            i++;
    }

    return (-1);
}

char *new_string(char *s)
{
    int i;
    int j;
    int len;
    char *s_new;

    s_new = (char *)malloc((strlen(s) + 1) * sizeof(char));
    if (!s_new)
        return (NULL);
    i = 0;
    j = 0;
    len = findSubstring(s);
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

void if_qoute_exit(t_shell *shell, char *s)
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

void	test_export(t_shell *shell_m, int i)
{
	char	**tmp;
	char	*str;
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
	else if (findSubstring(shell_m->cmnd[i]) != -1)
	{
		str = new_string(shell_m->cmnd[i]);
		if_qoute_exit(shell_m, str);
	}
	else
		if_qoute_exit(shell_m, shell_m->cmnd[i]);
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
