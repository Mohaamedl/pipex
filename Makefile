# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/04 20:30:00 by mhaddadi          #+#    #+#              #
#    Updated: 2025/08/04 20:30:00 by mhaddadi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program names
NAME = pipex
NAME_BONUS = pipex_bonus

# Source files
SRCS = pipex.c utils.c path.c
SRCS_BONUS = pipex_bonus.c pipex_bonus_utils.c pipex_bonus_heredoc.c utils.c path.c

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Library settings
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Default target
all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) -o $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(LIBFT) $(SRCS_BONUS)
	$(CC) $(CFLAGS) $(SRCS_BONUS) $(LIBFT) -o $(NAME_BONUS)

clean:
	rm -f $(NAME) $(NAME_BONUS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus
