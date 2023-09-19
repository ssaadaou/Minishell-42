#include "include/minishell.h"


bool	check_plus_egal(char *s)
{
	int		i;
	int		len;
	size_t	length;
	char	*plus_pos;

	if (ft_isdigit(s[0]))
		return (false);
	plus_pos = ft_strstr(s, "+=");
	if (!plus_pos)
		return (false);
	length = plus_pos - s;
	if (length > 0 && (s[length - 1] == '\'' || s[length - 1] == '\"'))
		len = length -1;
	else
		len = length;
	i = 0;
	while (i < len)
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

char	*extract_before_plus(char *s)
{
	char	*pos;
	size_t	len;
	char	*new_s;

	pos = strchr(s, '+');
	if (!pos)
		return (NULL);
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
	int pos;

	pos = find_first_equal_or_length(s);
	return (ft_substr(s, 0, pos - 1));
}


char	*extract_before_egal(char *s)
{
	char	*pos;
	size_t	len;
	char	*new_s;

	pos = strchr(s, '=');
	if (!pos)
		return (NULL);
	len = pos - s;
	new_s = (char *)malloc((len + 1) * sizeof(char));
	if (!new_s)
		return (NULL);
	ft_strncpy(new_s, s, len);
	new_s[len] = '\0';
	return (new_s);
}

char	**add_if_plus_exit(char **s, char *s_add)
{
	int		i;
	int		j;
	char	**new_s;
	int		len;

	len = set_size_arg(s);
	new_s = (char **)calloc(sizeof(char *), len + 1);
	if (!new_s)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] != NULL)
	{
		char *s1 = extract_before_egal(s[i]);
		char *s2 = extract_before_plus(s_add);
		if (!ft_strcmp(s1, s2) && s1 && s2)
		{
			char *s3 = extract_after_equal(s_add);
			new_s[j] = ft_strjoin(s[i], s3);
		}
		else
			new_s[j] = ft_strdup(s[i]);
		i++;
		j++;
	}
	new_s[j] = NULL;
	return (new_s);
}

// if (check_plus_egal(shell_m->cmnd[i]) && find_command(shell_m, shell_m->cmnd[i]))
// 	{
// 		tmp = add_if_plus_exit(shell_m->str, shell_m->cmnd[i]);
// 		freesplit(shell_m->str, 0);
// 		shell_m->str = tmp;
// 	}
// 	else
// 		printf("No Bro\n");

char	*extract_after_plus(char *s)
{
	char	*pos;
	size_t	len;
	char	*new_s;

	pos = strchr(s, '=');
	if (!pos)
		return (NULL);
	len = pos - s;
	new_s = (char *)malloc((len + 1) * sizeof(char));
	if (!new_s)
		return (NULL);
	ft_strncpy(new_s, s, len);
	new_s[len] = '\0';
	return (new_s);
}

char	*extract_after_equal_1(char *s)
{
	int pos;

	pos = find_first_equal_or_length(s);
	return (ft_substr(s, 0, pos));
}

char	*extract_before_plus_1(char *s)
{
	char	*pos;
	size_t	len;
	char	*new_s;

	pos = strchr(s, '+');
	if (!pos)
		return (NULL);
	len = pos - s;
	new_s = (char *)malloc((len + 1) * sizeof(char));
	if (!new_s)
		return (NULL);
	ft_strncpy(new_s, s, len);
	new_s[len] = '\0';
	return (new_s);
}

int	main(int ac, char **str)
{
	char *s[] = {"USER=ylamsiah",
				"LOGNAME=ylamsiah",
				"PAGER=less",
				NULL
				};
	int i = 0;
	while (s[i])
	{
		printf("%s\n", s[i++]);
	}
	printf("---------><---------\n");
	printf("%s\n", extract_before_plus_1(s[1]));
	printf("%s\n", extract_after_equal_1(s[1]));
	printf("%s\n", extract_after_plus(s[1]));
	printf("---------><---------\n");
	char **s_1 = add_if_plus_exit(s, str[1]);
	i = 0;
	while (s_1[i])
	{
		printf("%s\n", s_1[i]);
		i++;
	}
	return (0);
}
