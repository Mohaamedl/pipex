# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/27 09:11:07 by mhaddadi          #+#    #+#              #
#    Updated: 2025/04/27 09:11:16 by mhaddadi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                              libft MAKEFILE                              #
# **************************************************************************** #

# **************************************************************************** #
#                                CONFIGURATION                                 #
# **************************************************************************** #
# === Project Configuration ===
NAME                =   libft.a
CC                  =   cc
CFLAGS              =   -Wall -Wextra -Werror

SRC_DIR     =   src
BUILD_DIR   =   build
INC_DIR     =   inc

SRC_LIBFT = \
	$(SRC_DIR)/libft/ft_atoi.c \
	$(SRC_DIR)/libft/ft_atol.c \
	$(SRC_DIR)/libft/ft_bzero.c \
	$(SRC_DIR)/libft/ft_calloc.c \
	$(SRC_DIR)/libft/ft_isalnum.c \
	$(SRC_DIR)/libft/ft_isalpha.c \
	$(SRC_DIR)/libft/ft_isascii.c \
	$(SRC_DIR)/libft/ft_isdigit.c \
	$(SRC_DIR)/libft/ft_isprint.c \
	$(SRC_DIR)/libft/ft_isspace.c \
	$(SRC_DIR)/libft/ft_itoa.c \
	$(SRC_DIR)/libft/ft_memchr.c \
	$(SRC_DIR)/libft/ft_memcmp.c \
	$(SRC_DIR)/libft/ft_memcpy.c \
	$(SRC_DIR)/libft/ft_memmove.c \
	$(SRC_DIR)/libft/ft_memset.c \
	$(SRC_DIR)/libft/ft_putchar_fd.c \
	$(SRC_DIR)/libft/ft_putendl_fd.c \
	$(SRC_DIR)/libft/ft_putnbr_fd.c \
	$(SRC_DIR)/libft/ft_putstr_fd.c \
	$(SRC_DIR)/libft/ft_split.c \
	$(SRC_DIR)/libft/ft_strchr.c \
	$(SRC_DIR)/libft/ft_strdup.c \
	$(SRC_DIR)/libft/ft_striteri.c \
	$(SRC_DIR)/libft/ft_strjoin.c \
	$(SRC_DIR)/libft/ft_strlcat.c \
	$(SRC_DIR)/libft/ft_strlcpy.c \
	$(SRC_DIR)/libft/ft_strlen.c \
	$(SRC_DIR)/libft/ft_strmapi.c \
	$(SRC_DIR)/libft/ft_strcmp.c \
	$(SRC_DIR)/libft/ft_strncmp.c \
	$(SRC_DIR)/libft/ft_strnstr.c \
	$(SRC_DIR)/libft/ft_strrchr.c \
	$(SRC_DIR)/libft/ft_strtrim.c \
	$(SRC_DIR)/libft/ft_substr.c \
	$(SRC_DIR)/libft/ft_tolower.c \
	$(SRC_DIR)/libft/ft_toupper.c \
	$(SRC_DIR)/libft/ft_lstadd_back.c \
	$(SRC_DIR)/libft/ft_lstadd_front.c \
	$(SRC_DIR)/libft/ft_lstclear.c \
	$(SRC_DIR)/libft/ft_lstdelone.c \
	$(SRC_DIR)/libft/ft_lstiter.c \
	$(SRC_DIR)/libft/ft_lstlast.c \
	$(SRC_DIR)/libft/ft_lstmap.c \
	$(SRC_DIR)/libft/ft_lstnew.c \
	$(SRC_DIR)/libft/ft_lstsize.c

SRC_PRINTF = \
	$(SRC_DIR)/ft_printf/ft_printf.c \
	$(SRC_DIR)/ft_printf/ft_conversion_handler.c \
	$(SRC_DIR)/ft_printf/ft_parse_format.c \
	$(SRC_DIR)/ft_printf/ft_printchar.c \
	$(SRC_DIR)/ft_printf/ft_printhex.c \
	$(SRC_DIR)/ft_printf/ft_printnbr.c \
	$(SRC_DIR)/ft_printf/ft_printpercent.c \
	$(SRC_DIR)/ft_printf/ft_printptr.c \
	$(SRC_DIR)/ft_printf/ft_printstr.c \
	$(SRC_DIR)/ft_printf/ft_printunbr.c \
	$(SRC_DIR)/ft_printf/ft_putnchar.c \
	$(SRC_DIR)/ft_printf/ft_uitoa.c \
	$(SRC_DIR)/ft_printf/ft_hex_helper.c

SRC_GNL = \
	$(SRC_DIR)/gnl/get_next_line.c \
	$(SRC_DIR)/gnl/get_next_line_utils.c

SRC_BONUS = \
	$(SRC_DIR)/gnl/get_next_line_bonus.c \
	$(SRC_DIR)/gnl/get_next_line_utils_bonus.c

SRC = $(SRC_LIBFT) $(SRC_PRINTF) $(SRC_GNL)

OBJ = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
OBJ_BONUS = $(SRC_BONUS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# === Rules ===
all: $(NAME)

$(NAME): $(OBJ)
	@mkdir -p $(BUILD_DIR)
	ar rcs $@ $^

bonus: $(OBJ_BONUS)
	@mkdir -p $(BUILD_DIR)
	ar rcs $(NAME) $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
