# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/23 17:02:37 by ubuntu            #+#    #+#              #
#    Updated: 2025/03/13 17:30:53 by ubuntu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
SRCS_DIR	= srcs
OBJ_DIR 	= obj_$(NAME)
SRCS		= srcs/main.c \
			srcs/lexer/lexer_utilities.c \
			srcs/lexer/lexer_build_list_token.c \
			srcs/lexer/lexer_cleaning_input.c \
			srcs/lexer/lexer_initialisation.c \
			srcs/lexer/lexer_validate_operators.c \
			srcs/lexer/lexer.c \
			srcs/parser/parser_initialisation_list_cmd.c \
			srcs/parser/parser_initialisation.c \
			srcs/parser/parser.c \
			srcs/malloc/malloc_list.c \
			srcs/malloc/malloc_free.c \
			srcs/malloc/malloc_split_ml.c \
			srcs/malloc/malloc_strdup_ml.c \
			srcs/malloc/malloc_substr_ml.c \
			srcs/utilities/error.c \
			srcs/utilities/init.c \
			srcs/utilities/print.c
		
OBJS		= $(SRCS:$(SRCS_DIR)/%.c=$(OBJ_DIR)/%.o)
CC			= cc
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror -ggdb -I$(SRCS_DIR)
LIBFT_AR	= ./includes/libft/libft.a
PRINTF_AR	= ./includes/printf/printf.a

$(OBJ_DIR)/%.o : $(SRCS_DIR)/%.c
			@mkdir -p $(@D)
			$(CC) $(CFLAGS) -c $< -o $@
			
all:		$(NAME)
			
$(NAME):	$(OBJS) $(LIBFT_AR) $(PRINTF_AR)
			$(CC) $(OBJS) $(LIBFT_AR) $(PRINTF_AR) -o $(NAME) -lreadline
			@echo "\033[32m""Compilation de $(NAME) est terminée!""\033[0m"

$(LIBFT_AR):
			make -sC ./includes/libft

$(PRINTF_AR):
			make -sC ./includes/printf

clean:
			make clean -sC ./includes/libft
			make clean -sC ./includes/printf
			$(RM) $(OBJ_DIR)
			@echo "\033[36m""Répertoire $(OBJ_DIR) supprimé.""\033[0m"

fclean:		clean
			$(RM) $(LIBFT_AR)
			$(RM) $(PRINTF_AR)
			$(RM) $(NAME)
			@echo "\033[36m""Exécutable $(NAME) supprimé.""\033[0m"

re:			fclean 	all

.PHONY: all clean fclean re
