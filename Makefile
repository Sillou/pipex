# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alubrano <alubrano@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/08 12:34:20 by alubrano          #+#    #+#              #
#    Updated: 2026/01/14 16:52:57 by alubrano         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
GREEN	= \033[0;32m
RED		= \033[0;31m
RESET	= \033[0m

# Project
NAME	= pipex
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g

SRC_DIR	= src
OBJ_DIR	= obj
INC_DIR	= includes

SRC		=	pipex.c \
			utils.c

SRCS	= $(addprefix $(SRC_DIR)/, $(SRC))
OBJS	= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

#LIBFT
LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

INCLUDES	= -I$(INC_DIR) -I$(LIBFT_DIR)

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -o $(NAME)
	@echo "$(GREEN)✓ Build OK: $(NAME)$(RESET)"

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo "$(RED)✗ Objects removed$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "$(RED)✗ $(NAME) removed$(RESET)"

re: fclean all

.PHONY: all clean fclean re