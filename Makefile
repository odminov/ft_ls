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

SRC_POW =./main.c read_dir.c
OBJECT_POW = $(SRC_POW:.c=.o)

FLAGS = -Wall -Wextra -Werror

LIBS = lftprintf lft 

DIR_LIB = -L ./libft/

all: $(NAME)

$(NAME) : $(OBJECT_POW)
		make -C ./libft
		gcc -o $(NAME) $(FLAGS) $(OBJECT_POW) -L $(DIR_LIB) $(LIBS)
%.o: %.c
		gcc $(FLAGS) -o $@ -c $<
clean:
		make -C ./libft clean
		/bin/rm -f $(OBJECT_POW)
fclean: clean
		rm -rf ./libft/libft.a
		rm -rf ./libft/libftprintf.a
		rm -f $(NAME)
re:		fclean all
