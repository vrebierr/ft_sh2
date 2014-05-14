# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vrebierr <vrebierr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/05/14 14:38:49 by vrebierr          #+#    #+#              #
#    Updated: 2014/05/14 14:38:49 by vrebierr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_minishell2
SRC = main.c
OBJ = main.o builtins.o
FLAGS = -Wall -Werror -Wextra
LDIR = libft/
LIB = $(LDIR)libft.a
LFLAGS = -L $(LDIR) -lft

all: $(NAME)

$(NAME): $(LIB)
	gcc -o $(NAME) $(FLAGS) $(SRC) -I $(LDIR)inc $(LFLAGS)

$(LIB):
	make -C $(LDIR)

clean:
	make clean -C $(LDIR)
	rm -f $(OBJ)

fclean: clean
	make fclean -C $(LDIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
