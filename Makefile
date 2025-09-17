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

# Target name (always pipex)
NAME = pipex

# Detect which target is being built using MAKECMDGOALS
ifeq ($(filter bonus,$(MAKECMDGOALS)),bonus)
    # Bonus sources
    SRCS = src/pipex_bonus/pipex_bonus.c \
           src/pipex_bonus/utils_bonus.c \
           src/pipex_bonus/path_bonus.c \
           src/pipex_bonus/cmd_parse_bonus.c \
           src/pipex_bonus/heredoc_bonus.c
    COMPILE_TYPE = "Bonus"
    TYPE_FILE = .bonus_build
else
    # Mandatory sources  
    SRCS = src/pipex/pipex.c \
           src/pipex/utils.c \
           src/pipex/path.c \
           src/pipex/cmd_parse.c
    COMPILE_TYPE = "Mandatory"
    TYPE_FILE = .mandatory_build
endif

# Build directory for object files
BUILD_DIR = build

# Create object file paths in build directory
OBJS = $(addprefix $(BUILD_DIR)/, $(notdir $(SRCS:.c=.o)))
HEADER = -Iincludes
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT = libft/libft.a

all: ${LIBFT} check_type ${NAME}

bonus: ${LIBFT} check_type ${NAME}

# Check if build type changed and force rebuild if needed
check_type:
	@if [ ! -f $(TYPE_FILE) ]; then \
		rm -f .mandatory_build .bonus_build $(NAME); \
		touch $(TYPE_FILE); \
	fi

${NAME}: ${OBJS} ${LIBFT}
	@$(CC) ${OBJS} -Llibft -lft -o ${NAME}
	@echo "\033[32m$(COMPILE_TYPE) Pipex Compiled! ᕦ(\033[31m♥\033[32m_\033[31m♥\033[32m)ᕤ\n"

${LIBFT}:
	@make -C libft

# Create build directories and compile object files
# Create build directories and compile object files
$(BUILD_DIR)/%.o: src/pipex/%.c
	@mkdir -p $(BUILD_DIR)
	@gcc ${CFLAGS} ${HEADER} -c $< -o $@

$(BUILD_DIR)/%.o: src/pipex_bonus/%.c
	@mkdir -p $(BUILD_DIR)
	@gcc ${CFLAGS} ${HEADER} -c $< -o $@

$(BUILD_DIR)/%.o: src/pipex_bonus/%.c
	@mkdir -p $(BUILD_DIR)
	@gcc ${CFLAGS} ${HEADER} -c $< -o $@

clean:
	@make clean -C ./libft
	@rm -rf $(BUILD_DIR)

fclean: clean
	@make fclean -C ./libft
	@rm -f ${NAME} .mandatory_build .bonus_build
	@echo "\n\033[31mDeleting EVERYTHING! ⌐(ಠ۾ಠ)¬\n"

re: fclean all

re_bonus: fclean bonus

party:
	@printf "\033c"
	@echo "\n\033[35m♪┏(・o･)┛♪"
	@sleep 1
	@printf "\033c"
	@echo "\033[1;33m♪┗(・o･)┓♪"
	@sleep 1
	@printf "\033c"
	@echo "\n\033[36m♪┏(・o･)┛♪"
	@sleep 1
	@printf "\033c"
	@echo "\033[34m♪┗(・o･)┓♪\n"

# Valgrind rules
valgrind: ${NAME}
	@echo "\033[33m  Running Valgrind (basic)...\033[0m"
	valgrind --trace-children=yes --track-fds=yes --leak-check=full ./$(NAME) input.txt "cat" "wc -l" output.txt

vfull: ${NAME}
	@echo "\033[33m  Running Valgrind (detailed)...\033[0m"
	valgrind --trace-children=yes --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) input.txt "cat" "wc -l" output.txt

vtest: ${NAME}
	@echo "\033[33m  Running Valgrind with custom test...\033[0m"
	@echo "\033[36mUsage: make vtest ARGS='input.txt \"cmd1\" \"cmd2\" output.txt'\033[0m"
	valgrind --trace-children=yes --track-fds=yes --leak-check=full ./$(NAME) $(ARGS)

vbonus:
	@make bonus
	@echo "\033[33m  Running Valgrind (bonus test)...\033[0m"
	@echo -e "test1\ntest2\nEOF\nextra" | valgrind --trace-children=yes --track-fds=yes --leak-check=full ./$(NAME) here_doc EOF "grep test" "wc -l" output.txt || true
	@echo "\033[32m  Valgrind bonus test completed!\033[0m"

vquick: ${NAME}
	@echo "\033[33m  Running Valgrind (quick check)...\033[0m"
	valgrind --track-fds=yes --leak-check=yes ./$(NAME) input.txt "cat" "wc -l" output.txt

vhelp:
	@echo "\033[32m  Valgrind Commands:\033[0m"
	@echo "\033[36m  make valgrind\033[0m  - Basic valgrind test with cat | wc -l"
	@echo "\033[36m  make vfull\033[0m     - Detailed valgrind with all leak kinds"
	@echo "\033[36m  make vquick\033[0m    - Quick valgrind check"
	@echo "\033[36m  make vbonus\033[0m    - Test bonus (heredoc) with valgrind"
	@echo "\033[36m  make vtest ARGS='...'\033[0m - Custom test"
	@echo "\033[33m  Example: make vtest ARGS='input.txt \"ls -l\" \"wc -l\" output.txt'\033[0m"

.PHONY: all clean fclean re re_bonus bonus party valgrind vfull vtest vbonus vquick vhelp check_type
