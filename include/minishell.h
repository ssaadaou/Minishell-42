/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:28:44 by shamsate          #+#    #+#             */
/*   Updated: 2023/09/19 20:05:14 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <string.h>
# include <signal.h>
# include <unistd.h>
# include <curses.h>
# include <limits.h>
# include <termios.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_list	t_list;
typedef struct s_shell	t_shell;

# define ERROR	-1
# define WELCOME  "\n \
	\033[1;34m╔══════════════════════════════════════════════════════════════════════════════════╗\033[34m\n\
	\033[1;34m║\033[34m   \033[1;31m███╗   ███╗ ██╗ ███╗   ██╗ ██╗ ███████╗ ██╗  ██╗  ███████╗ ██║      ██║      \033[34m  \033[1;34m║\033[34m\n\
	\033[1;34m║\033[34m   \033[1;31m████╗ ████║ ██║ ████╗  ██║ ██║ ██╔════╝ ██║  ██║  ██╔════╝ ██║      ██║        \033[34m\033[1;34m║\033[34m\n\
	\033[1;34m║\033[34m   \033[1;31m██╔████╔██║ ██║ ██╔██╗ ██║ ██║ ███████╗ ███████║  █████╗   ██║      ██║        \033[34m\033[1;34m║\033[34m\n\
	\033[1;34m║\033[34m   \033[1;31m██║╚██╔╝██║ ██║ ██║╚██╗██║ ██║ ╚════██║ ██╔══██║  ██╔══╝   ██║      ██║        \033[34m\033[1;34m║\033[34m\n\
	\033[1;34m║\033[34m   \033[1;31m██║ ╚═╝ ██║ ██║ ██║ ╚████║ ██║ ███████║ ██║  ██║  ███████╗ ███████╗ ███████╗   \033[34m\033[1;34m║\033[34m\n\
	\033[1;34m║\033[34m   \033[1;31m╚═╝     ╚═╝ ╚═╝ ╚═╝  ╚═══╝ ╚═╝ ╚══════╝ ╚═╝  ╚═╝  ╚══════╝ ╚══════╝ ╚══════╝   \033[34m\033[1;34m║\033[34m\n\
	\033[1;34m╚═══════════════════════════════════════════════════\
═══════════════════════════════╝\033[34m\n"

typedef struct s_list
{
	struct s_list	*next;
	int				content;
}	t_list;

typedef struct s_shell
{
	char			*cp;
	bool			test;
	char			**str;
	char			*_pwd;
	char			*path;
	struct s_shell	*next;
	char			**cmnd;
	char			*_oldpwd;
	t_list			*cmd_list;
}			t_shell;

// minishell fonction

//-->Utils of Minishell
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				is_all_digit(char *s);
int				set_size_arg(char **s);
t_list			*ft_lstnew(int content);
size_t			ft_strlen(const char *s);
t_list			*ft_lstlast(t_list *lst);
char			*ft_strdup(const char *s);
int				lst_size_cmd(t_list *lst);
void			freesplit(char **s, int i);
long long int	atoi_exit(const char *str);
void			ft_bzero(void *s, size_t n);
int				count(char const *s, char c);
void			ft_putstr_fd(char *s, int fd);
void			ft_putchar_fd(char c, int fd);
int				ft_strcmp(char *s1, char *s2);
char			*ft_strchr(const char *s, int c);
char			**ft_split(char const *s, char c);
char			*ft_strcpy(char *dest, char *src);
char			*ft_strstr(char *str, char *to_find);
void			*ft_memset(void *s, int c, size_t n);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strjoin(char const *s1, char const *s2);
void			ft_lstadd_back(t_list **lst, t_list *new_cmd);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strncpy(char *dest, const char *src, unsigned int n);
char			*ft_substr(char const *s, unsigned int start, size_t len);

//->src

//-->executable
bool			is_buil(t_shell *msh);
void			mini_exec(t_shell *m_sh);

//-->parsing
char			**ft_comdup(char **str);
void			sig_ctlc(int input_sig);
void			mini_shell_w(t_shell *cmd);

//-->builtins

//x:--->"utils of builtins"
void			search_p_o_p(t_shell *cmd);
void			free_minishell(t_shell *shell);
char			*find_path(t_shell *mini_s, char *find);

//x:---> "export":
int				check_input(char *s);
int				check_valid_id(char c);
void			shell_export(t_shell *sh);
char			*remove_quotes(char *s, char c);
char			*remove_double_quotes(char *str);
char			*ft_strd(char *s, t_shell *sh_m);
int				check_char(t_shell *cmd, char *s);
int				search_plus(char *s, char d_quot);
void			test_export(t_shell *shell_m, int i);
int				export_unset_err(char *cmd, char *s);
int				find_first_equal_or_length(char *str);
char			**add_var_export(char **shell, char *str);
int				find_command(t_shell *shell_m, char *sh_cmnd);
bool			check_command_export(t_shell *sh_m, char *cmd);
char			**loop_add_var(char **arr, char **rtn, const char *str);

//x:---> "env":
void			shell_env(t_shell *cmd);
char			*ft_strd(char *s, t_shell *sh_m);

//x:---> "exit":
void			shell_exit(t_shell *cmd);

//x:---> "pwd":
void			shell_pwd(t_shell *cmd);

//x:---> "unset":
bool			check_cmnd_unset(char *s);
void			shell_unset(t_shell *sh_m);
char			**del_var(char *cmd, char **env);
bool			check_syntax_cmd(char *env, char *cmnd);
char			**loop_add_env(char *str, char **env, char **cmd);

//x:---> "echo":
void			shell_echo(t_shell *cmd);
bool			is_single_hyphen_n(char *s);

//x:---> "cd":
void			change_path(t_shell *cmd);
void			check_cd_arg(t_shell *cmd);
void			shell_cd(t_shell *shell_m);
void			add_up_to_env(t_shell *m_shell);
int				check_way(char *cmd, t_shell *cm);

////
int findSubstring(const char *str);

#endif