NAME = Minishell

YELLOW	=	$(shell tput -Txterm setaf 4)
GREEN	=	$(shell tput -Txterm setaf 5)

C_BLUE  = \033[1;34m
C_CYAN  = \033[1;36m
C_RESET = \033[34m

CC      = cc

RM      = rm -rf

CFLAGS  = -Wall -Wextra -Werror

READLINE = -lreadline

LIB = -L/Users/ylamsiah/.brew/opt/readline/lib
INC = -I/Users/ylamsiah/.brew/opt/readline/include

HEADER  = include/minishell.h

O_DIR   := OBJ_DER

PARS = $(addprefix src/parsing/, signal_mshell.c mini_shell_w.c add_arg.c)


BUIL = $(addprefix src/builtins/, shell_export/shell_export.c shell_export/shell_export_utils_2.c \
	shell_export/shell_export_utils_1.c shell_pwd.c shell_echo.c find_p.c shell_exit.c shell_env.c \
	shell_cd.c shell_unset.c)


EXEC = $(addprefix src/executable/, mini_execute.c)


UTIL = $(addprefix src/utils/, is_all_digit.c ft_substr.c ft_strlen.c ft_strcmp.c ft_strjoin.c ft_strdup.c \
	ft_split.c ft_putstr_fd.c ft_putchar_fd.c atoi_exit.c ft_lstadd_back.c ft_lstlast.c size_cmd_list.c \
	ft_lstnew.c ft_calloc.c ft_strncmp.c ft_strlcpy.c ft_memmove.c ft_memcpy.c ft_isalpha.c ft_isalnum.c \
	ft_strchr.c ft_strcpy.c ft_strstr.c set_size_arg.c)


M_SRCS = minishell.c $(UTIL) $(EXEC) $(PARS) $(BUIL)

M_OBJS = $(patsubst %.c,$(O_DIR)/%.o,$(M_SRCS))

all: $(NAME)

Prj_Name = "\n" \
	"$(YELLOW)███$(GREEN)╗   $(YELLOW)███$(GREEN)╗ $(YELLOW)██$(GREEN)╗ $(YELLOW)███$(GREEN)╗  $(YELLOW)\
	██$(GREEN)╗ $(YELLOW)██$(GREEN)╗ $(YELLOW)███████$(GREEN)╗ $(YELLOW)██$(GREEN)╗  $(YELLOW)██$(GREEN)╗ \
	$(YELLOW)███████$(GREEN)╗ $(YELLOW)██$(GREEN)║      $(YELLOW)██$(GREEN)║     \n" \
	"$(YELLOW)████$(GREEN)╗ $(YELLOW)████$(GREEN)║ $(YELLOW)██$(GREEN)║ $(YELLOW)████$(GREEN)╗  $(YELLOW)██$(GREEN)║\
	 $(YELLOW)██$(GREEN)║ $(YELLOW)██$(GREEN)╔════╝ $(YELLOW)██$(GREEN)║  $(YELLOW)██$(GREEN)║\
	  $(YELLOW)██$(GREEN)╔════╝ $(YELLOW)██$(GREEN)║      $(YELLOW)██$(GREEN)║     \n" \
	"$(YELLOW)██$(GREEN)╔$(YELLOW)████$(GREEN)╔$(YELLOW)██$(GREEN)║ $(YELLOW)██$(GREEN)║ \
	$(YELLOW)██$(GREEN)╔$(YELLOW)██$(GREEN)╗ $(YELLOW)██$(GREEN)║ $(YELLOW)██$(GREEN)║\
	 $(YELLOW)███████$(GREEN)╗ $(YELLOW)███████$(GREEN)║ \
	 $(YELLOW)█████$(GREEN)╗   $(YELLOW)██$(GREEN)║      $(YELLOW)██$(GREEN)║     \n" \
	"$(YELLOW)██$(GREEN)║╚$(YELLOW)██$(GREEN)╔╝$(YELLOW)██$(GREEN)║ $(YELLOW)██$(GREEN)║\
	 $(YELLOW)██$(GREEN)║╚$(YELLOW)██$(GREEN)╗$(YELLOW)██$(GREEN)║ $(YELLOW)██$(GREEN)║ \
	 ╚════$(YELLOW)██$(GREEN)║ $(YELLOW)██$(GREEN)╔══$(YELLOW)██$(GREEN)║ \
	 $(YELLOW)██$(GREEN)╔══╝   $(YELLOW)██$(GREEN)║      $(YELLOW)██$(GREEN)║     \n" \
	"$(YELLOW)██$(GREEN)║ $(GREEN)╚═╝ $(YELLOW)██$(GREEN)║ $(YELLOW)██$(GREEN)║ $(YELLOW)██$(GREEN)║ \
	$(GREEN)╚$(YELLOW)████$(GREEN)║ $(YELLOW)██$(GREEN)║ $(YELLOW)███████$(GREEN)║ \
	$(YELLOW)██$(GREEN)║  $(YELLOW)██$(GREEN)║ $(YELLOW)███████$(GREEN)╗ $(YELLOW)███████$(GREEN)╗ $(YELLOW)███████$(GREEN)╗\n" \
	"$(GREEN)╚═╝     $(GREEN)╚═╝ $(GREEN)╚═╝ $(GREEN)╚═╝  $(GREEN)╚═══╝ $(GREEN)╚═╝\
	 $(GREEN)╚══════╝ $(GREEN)╚═╝  $(GREEN)╚═╝ $(GREEN)╚══════╝ $(GREEN)╚══════╝\
	  $(GREEN)╚══════╝\n$(C_RESET)" \


$(NAME): $(M_OBJS) $(HEADER)
	@echo $(Prj_Name)
	@$(CC) $(CFLAGS) $(M_OBJS) $(READLINE) $(LIB) -o $(NAME)
	@echo "$(C_BLUE)		✅ Compilation completed successfully!$(C_RESET)"

$(O_DIR)/%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:
	@$(RM) $(O_DIR)
	@echo "$(C_CYAN)🗑️  Object Directory has been removed......$(C_RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(C_CYAN)	🚀 'Minishell' executable has been removed.....$(C_RESET)"

re: fclean all

.PHONY: all clean fclean re