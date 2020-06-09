# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wkorande <willehard@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 13:58:13 by wkorande          #+#    #+#              #
#    Updated: 2020/06/09 13:45:45 by wkorande         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = visualizer

CFLAGS = -Wall -Wextra -Werror

SRCS = visualizer.c

LEM_IN_SRCS = env.c\
				link.c\
				room.c\
				debug.c

SRCDIR = src

LEM_IN_SRCDIR = ../src

SRC = $(addprefix $(SRCDIR)/, $(SRCS)) $(addprefix $(LEM_IN_SRCDIR)/, $(LEM_IN_SRCS))

OUT = $(SRCS:.c=.o)

INCL = include

LIBFT= ../libft

FLAGS= -Wall -Wextra -Werror

SDLFLAGS = `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lm

all: $(NAME)

$(NAME):
	make -C $(LIBFT)
	clang $(FLAGS) -o $(NAME) -I$(INCL) -I $(LIBFT)/includes -I../include -I /Users/wkorande/.brew/include $(SRC) -L$(LIBFT) -lft $(SDLFLAGS)
	#gcc -g $(FLAGS) -o $(NAME) -I$(INCL) -I $(LIBFT)/includes -I../include $(SRC) -L$(LIBFT) -lft

debug:
	clang -g $(FLAGS) -o $(NAME) -I$(INCL) -I $(LIBFT)/includes -I../include $(SRC) -L$(LIBFT) -lft $(SDLFLAGS)

clean:
	@echo "Removing object files ..."
	@rm -f $(OBJ)

fclean : clean
	@echo "Removing $(NAME) ..."
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
