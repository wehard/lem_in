# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 13:58:13 by wkorande          #+#    #+#              #
#    Updated: 2020/03/20 14:50:15 by wkorande         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

CFLAGS = -Wall -Wextra -Werror

SRC = main.c\
	room.c\
	link.c\
	env.c\
	bfs_queue.c\
	path.c\
	debug.c\
	graph.c\
	flow.c

SRCDIR = src

SRCS = $(addprefix $(SRCDIR)/, $(SRC))

OBJS = $(SRC:.c=.o)

INCL = include

LIBFT= libft

FLAGS= -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	make -C libft
	clang $(FLAGS) -DBUFFSIZE1 -o $(NAME) -I$(INCL) -I $(LIBFT)/includes $(SRCS) -L$(LIBFT) -lft -lm -O2

debug:
	make -C libft
	clang -g $(FLAGS) -DBUFFSIZE1 -o $(NAME) -I$(INCL) -I $(LIBFT)/includes $(SRCS) -L$(LIBFT) -lft -lm

clean:
	@printf "Removing objects\n"
	@rm -f $(OBJS)

fclean : clean
	@printf "Removing $(NAME)\n"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re debug
