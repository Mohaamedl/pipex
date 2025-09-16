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
# TODO: add makegoals to complite bonus part with the same name
# Program names
NAME = pipex
NAME_BONUS = pipex

SRCS_DIR = src/pipex
SRCS_BONUS_DIR =src/pipex_bonus
RM = rm -rf
# Source files
SRCS = $(SRCS_DIR)/pipex.c \
			  $(SRCS_DIR)/utils.c \
			  $(SRCS_DIR)/path.c \
			  $(SRCS_DIR)/cmd_parse.c

SRCS_BONUS = $(SRCS_BONUS_DIR)/pipex_bonus.c \
						 $(SRCS_BONUS_DIR)/pipex_utils_bonus.c \
						 $(SRCS_BONUS_DIR)/pipex_heredoc_bonus.c \
						 $(SRCS_BONUS_DIR)/utils.c \
						 $(SRCS_BONUS_DIR)/path.c \
						 $(SRCS_BONUS_DIR)/cmd_parse.c

BUILD_DIR = build

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Library settings
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a


OBJS = $(SRCS:$(SRCS_DIR)%.c=$(BUILD_DIR)/%.o)
OBJS_BONUS = $(SRCS_BONUS:$(SRCS_BONUS_DIR)/%.c=$(BUILD_DIR)/%.o)

# Default target
create_dirs:
	@mkdir -p build/pipex
	@mkdir -p build/pipex_bonus


# Targets
all: $(NAME)

$(NAME): create_dirs $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)

# Compile .c to .o in build/
$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

bonus: $(BONUS_NAME)

$(BONUS_NAME): create_dirs $(OBJS_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -L$(LIBFT_DIR) -lft -o $(BONUS_NAME)


$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(RM) $(BUILD_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all


.PHONY: all clean fclean re bonus

