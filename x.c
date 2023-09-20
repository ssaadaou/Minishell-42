#include "include/minishell.h"
#include <string.h>
//yes
int	find_first_equal_or_length_1(char *str)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == '=')
			return (i + 1);
		i++;
	}
	return (len);
}
//yes
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
	strncpy(new_s, s, len);
	new_s[len] = '\0';
	return (new_s);
}
//yes
char	*extract_after_equal(char *s)
{
	int pos;

	pos = find_first_equal_or_length_1(s);
	return (ft_strdup(s + pos));
}


//yes
int	check_valid_id_1(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '[' || \
	c == ']' || c == '\'' || c == '\"' || c == ' ' || \
	c == ',' || c == '.' || c == ':' || c == '/' || \
	c == '{' || c == '}' || c == '+' || c == '^' || \
	c == '%' || c == '#' || c == '@' || c == '!' || \
	c == '~' || c == '=' || c == '-' || c == '?' || \
	c == '&' || c == '*');
}
//yes
bool	check_para(char *s)
{
	int	i;
	int	len;

	if (ft_isdigit(s[0]))
		return (false);
	if (s[0] == '=')
		return (false);
	i = 0;
	len = find_first_equal_or_length_1(s);
	while (i < len)
	{
		if (check_valid_id_1(*(s + i)))
			return (false);
		i++;
	}
	return (true);
}
//yes
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


char	*extract_before_equal(char *s)
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
		char *s1 = extract_before_equal(s[i]);
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

int main(int ac, char **str)
{
    char *name_before_plus = extract_before_plus(str[1]);
    char *name_after_equal = extract_after_equal(str[1]);
    char *s[] = {
        "na_me=John",
        "age=52",
        "ciy=New York",
        "name=Jane",
        "name_1=holls",
        NULL // NULL-terminated array
    };

    printf("--->%s\n", name_before_plus);
    printf("--->%s\n", name_after_equal);

    printf("\n\n-------------><-------------\n\n");
    int i = 0;
    while (s[i])
    {
        printf("%s ---> Yes\n", s[i]);
        i++;
    }
    printf("\n\n-------------><-------------\n\n");
    char **new_s = add_if_plus_exit(s, str[1]); 
    i = 0;
    while (new_s[i])
    {
        printf("%s ---> Yes\n", new_s[i]);
        i++;
    }
}