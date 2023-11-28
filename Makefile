NAME				=	minishell

COMPILE				=	cc

FLAGS				=	-Wall -Wextra -Werror

LDFLAGS				= 	-lreadline

COLOR_RESET			=	\033[0m
COLOR_CYAN			=	\033[36m
COLOR_GREEN			=	\033[32m
COLOR_RED			=	\033[31m

INCLUDE				=	libft/

SRCS_FOLDER			=	srcs/

SRCS_CD				=	own_cd
SRCS_ECHO			=	own_echo own_echo_helper
SRCS_ENV			=	own_env
SRCS_EXPORT			=	own_export export_helper
SRCS_HEREDOC		=	heredoc heredoc_helper
SRCS_REDIR			=	cut_redir_outfile cut_string_infile get_file last_builtin last_redir redir_helper_1 redir_helper_2
SRCS_PIPES			=	only_pipes pipex
SRCS_MODDED_Q		=	modded_split_for_qoutes split_helper
SRCS_MODDED			=	modded_split_lst modded_split_pipe
SRCS_MAIN			=	main loop
SRCS_UTILS			=	check_input get_path utils_1 utils_2 utils_3 execute check_quotes no_tokens check_builtins

SRCS				=	$(addsuffix .c, $(addprefix builtins/cd/, $(SRCS_CD))) \
						$(addsuffix .c, $(addprefix builtins/echo/, $(SRCS_ECHO))) \
						$(addsuffix .c, $(addprefix builtins/env/, $(SRCS_ENV))) \
						$(addsuffix .c, $(addprefix builtins/export/, $(SRCS_EXPORT))) \
						$(addsuffix .c, $(addprefix builtins/heredoc/, $(SRCS_HEREDOC))) \
						$(addsuffix .c, $(addprefix redirects/, $(SRCS_REDIR))) \
						$(addsuffix .c, $(addprefix pipes/, $(SRCS_PIPES))) \
						$(addsuffix .c, $(addprefix modded/quotes/, $(SRCS_MODDED_Q))) \
						$(addsuffix .c, $(addprefix modded/, $(SRCS_MODDED))) \
						$(addsuffix .c, $(addprefix main/, $(SRCS_MAIN))) \
						$(addsuffix .c, $(addprefix utils/, $(SRCS_UTILS))) \

OBJS				=	$(addprefix $(SRCS_FOLDER),$(SRCS:.c=.o))

all: $(NAME)

$(NAME):			$(INCLUDE) $(OBJS)
					@cd $(INCLUDE) && make
					@$(COMPILE) $(FLAGS) -o $(NAME) $(OBJS) -L$(INCLUDE) -lft $(LDFLAGS)
					@echo "$(COLOR_CYAN)Kompilierung abgeschlossen: $(NAME)$(COLOR_RESET)"

%.o: %.c
					@$(COMPILE) $(FLAGS) -c $< -o $@
					@echo "$(COLOR_GREEN)Kompilierung abgeschlossen: $@$(COLOR_RESET)"

clean:
					@echo "$(COLOR_RED)Cleanup MiniShell.$(COLOR_RESET)"
					@rm -f $(OBJS)
					@echo "$(COLOR_RED)Cleanup Libft.$(COLOR_RESET)"
					@cd $(INCLUDE) && make clean
					@echo "$(COLOR_GREEN)Cleanup completed.$(COLOR_RESET)"

fclean:				clean
					@echo "$(COLOR_RED)Start Full-Clean.$(COLOR_RESET)"
					@rm -f $(NAME)
					@echo "$(COLOR_RED)Full-Clean Libft.$(COLOR_RESET)"
					@cd $(INCLUDE) && make fclean
					@echo "$(COLOR_GREEN)Full-Clean completed.$(COLOR_RESET)"

re:					fclean all

.PHONY:				all clean fclean re
