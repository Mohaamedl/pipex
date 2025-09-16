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
PROG	= pipex
PROG_B  = pipex_bonus

SRCS 	= src/pipex/pipex.c \
				src/pipex/utils.c \
				src/pipex/path.c \
				src/pipex/cmd_parse.c

OBJS 	= ${SRCS:.c=.o}
MAIN	= src/pipex/pipex.c

SRCS_B	= src/pipex_bonus/pipex_bonus.c \
					src/pipex_bonus/utils_bonus.c \
					src/pipex_bonus/path_bonus.c \
					src/pipex_bonus/cmd_parse_bonus.c \
					src/pipex_bonus/heredoc_bonus.c \
					src/pipex/utils.c
OBJS_B	= ${SRCS_B:.c=.o}
MAIN_B	= src/pipex_bonus/pipex_bonus.c

HEADER	= -Iincludes

CC 		= cc
CFLAGS 	= -Wall -Wextra -Werror -g

.c.o:		%.o : %.c
					@gcc ${CFLAGS} ${HEADER} -c $< -o $(<:.c=.o)

all: 		${PROG}

${PROG}:	${OBJS}
					@echo "\033[33m----Compiling lib----"
					@make re -C ./libft
					@$(CC) ${OBJS} -Llibft -lft -o ${PROG}
					@echo "\033[32mPipex Compiled! ᕦ(\033[31m♥\033[32m_\033[31m♥\033[32m)ᕤ\n"


bonus:		${PROG_B}

${PROG_B}:	${OBJS_B}
					@echo "\033[33m----Compiling lib----"
					@make re -C ./libft
					@$(CC) ${OBJS_B} -Llibft -lft -o ${PROG_B}
					@echo "\033[32mPipex Bonus Compiled! ᕦ(\033[31m♥\033[32m_\033[31m♥\033[32m)ᕤ\n"

clean:
					@make clean -C ./libft
					@rm -f ${OBJS} ${OBJS_B}

fclean: 	clean
					@make fclean -C ./libft
					@rm -f $(NAME)
					@rm -f ${PROG}
					@echo "\n\033[31mDeleting EVERYTHING! ⌐(ಠ۾ಠ)¬\n"

re:			fclean all

re_bonus:	fclean bonus

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

.PHONY: all clean fclean re re_bonus bonus party
