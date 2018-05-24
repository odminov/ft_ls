#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/09 18:42:23 by ahonchar          #+#    #+#              #
#    Updated: 2018/05/23 21:22:23 by ahonchar         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ft_ls

FLAGS = -Wall -Wextra -Werror

HEADERS = ft_ls.h

SRC_POW =./main.c read_dir.c
OBJECT_POW = $(SRC_POW:.c=.o)

LIBS = lftprintf lft 

DIR_LIB = -L ./libft/

all: $(NAME)

$(NAME) : $(OBJECT_POW)
		make -C ./libft
		gcc -o $(NAME) $(FLAGS) $(OBJECT_POW) -L $(DIR_LIB) $(LIBS)

%.o: %.c $(HEADERS)
		gcc $(FLAGS) -o $@ -c $<

clean:
	make -C ./libft/ $@
	/bin/rm -f $(OBJECT_POW)

fclean: clean
	make -C ./libft/ $@
	rm -f $(NAME)

re:		fclean all
