# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/16 16:32:57 by adi-nata          #+#    #+#              #
#    Updated: 2023/06/16 12:49:00 by adi-nata         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philosophers

SRC_DIR	=	src

OBJ_DIR	=	obj

SRCS    =   src/philosophers.c		src/tools.c		src/simulation.c \
			src/libft.c				src/death.c

OBJS	=	$(addprefix obj/,$(notdir $(SRCS:.c=.o)))

CC		=	gcc

RM		=	rm -rf

FLAGS	=	-g -I./ -Wall -Wextra -Werror -pthread #-fsanitize=thread 


CLR_RMV		= \033[0m
RED		    = \033[1;31m
GREEN		= \033[1;32m
YELLOW		= \033[1;33m
BLUE		= \033[1;34m
CYAN 		= \033[1;36m


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
			@mkdir -p $(OBJ_DIR)
			@$(CC) $(FLAGS) -c $< -o $@

${NAME}:	${OBJS}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			@${CC} ${FLAGS} ${OBJS} -o ${NAME}
			@echo "$(GREEN)$(NAME) created[0m ✔️"

all:		${NAME}

objs:
			@mkdir -p obj

clean:
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"
			@${RM} obj


fclean:		clean
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"
			@${RM} ${NAME}


re:			fclean all

.PHONY:		all clean fclean re
