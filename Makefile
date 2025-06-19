# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
SRCS_DIR	= srcs
OBJ_DIR 	= obj_$(NAME)
SRCS		= srcs/main.c \
			srcs/lexer/lexer.c \
			srcs/lexer/lexer_initialisation.c \
			srcs/lexer/lexer_cleaning_input.c \
			srcs/lexer/lexer_build_list_token.c \
			srcs/lexer/lexer_utilities.c \
			srcs/parser/parser.c \
			srcs/parser/parser_initialisation.c \
			srcs/parser/parser_clear_and_expand.c \
			srcs/parser/parser_markers_expand.c \
			srcs/parser/parser_clear_elem.c \
			srcs/parser/parser_expand.c \
			srcs/parser/parser_valid_syntax.c \
			srcs/parser/parser_initialisation_list_cmd.c \
			srcs/parser/parser_handle_cmd.c \
			srcs/parser/parser_handle_hd.c \
			srcs/parser/parser_handle_redir.c \
			srcs/parser/parser_heredoc.c \
			srcs/parser/parser_fill_list_cmd.c \
			srcs/parser/parser_utilities_0.c \
			srcs/parser/parser_utilities_1.c \
			srcs/malloc/malloc_list.c \
			srcs/malloc/malloc_free.c \
			srcs/malloc/malloc_itoa_ml.c \
			srcs/malloc/malloc_split_ml.c \
			srcs/malloc/malloc_strdup_ml.c \
			srcs/malloc/malloc_strjoin_ml.c \
			srcs/malloc/malloc_substr_ml.c \
			srcs/utilities/error.c \
			srcs/utilities/handle_input.c \
			srcs/utilities/handle_quotes.c \
			srcs/utilities/init.c \
			srcs/utilities/print.c \
			srcs/utilities/utilities.c \
			srcs/builtin/builtin_echo.c \
			srcs/builtin/builtin_export.c \
			srcs/builtin/builtin_pwd.c \
			srcs/builtin/builtin_unset.c \
			srcs/builtin/builtin_utilities_0.c \
			srcs/builtin/builtin_utilities_1.c \
			srcs/builtin/builtin_utilities_2.c \
			srcs/builtin/ft_cd.c \
			srcs/builtin/ft_env.c \
			srcs/builtin/ft_exit.c \
			srcs/signals/signals.c \
			srcs/new_exec/debug_utils.c\
			srcs/new_exec/exec.c \
			srcs/new_exec/exec_utils.c \
			srcs/new_exec/exec_path.c \
			srcs/new_exec/exec_start.c \
			srcs/utilities/error2.c \
			srcs/utilities/paul_free.c \
			srcs/new_redirs/redirections.c \
			srcs/new_redirs/set_files.c


OBJS		= $(SRCS:$(SRCS_DIR)/%.c=$(OBJ_DIR)/%.o)
CC			= cc
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror -ggdb -I$(SRCS_DIR)
LIBFT_AR	= ./includes/libft/libft.a

$(OBJ_DIR)/%.o : $(SRCS_DIR)/%.c
			@mkdir -p $(@D)
			@$(CC) -g $(CFLAGS) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS) $(LIBFT_AR)
			@$(CC) $(OBJS) $(LIBFT_AR) -o $(NAME) -lreadline -g
			@echo "\033[32m""Compilation de $(NAME) est terminée!""\033[0m"

debug:		$(OBJS) $(LIBFT_AR)
			@$(CC) $(OBJS) $(LIBFT_AR) -o $(NAME)_debug -lreadline -g
			@echo "\033[33m""Compilation de $(NAME)_debug (mode debug) est terminée!""\033[0m"

leaks:
	    @echo "\033[33m""Lancement de $(NAME) avec Valgrind pour check leaks""\033[0m"
	    valgrind --suppressions=readline.supp --trace-children=yes --track-fds=yes --leak-check=full --show-leak-kinds=all ./$(NAME)_debug

$(LIBFT_AR):
			@make -sC ./includes/libft

clean:
			@make clean -sC ./includes/libft
			@$(RM) $(OBJ_DIR)
			@echo "\033[36m""Répertoire $(OBJ_DIR) supprimé.""\033[0m"

fclean:		clean
			@$(RM) $(LIBFT_AR)
			@$(RM) $(NAME)
			@echo "\033[36m""Exécutable $(NAME) supprimé.""\033[0m"

re:			fclean 	all

.PHONY: all clean fclean re
