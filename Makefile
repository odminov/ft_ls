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

HEADERS = ft_ls.h ./libft/libft.h ./libft/ft_printf/ft_printf.h

SRC_POW = main.c read_dir.c perm_and_time.c create_list.c flags.c lengths.c
OBJECT_POW = $(SRC_POW:.c=.o)

DIR_LIB = ./libft

all: $(NAME)

$(NAME) : $(OBJECT_POW)		
		gcc -o $(NAME) $(FLAGS) $(OBJECT_POW) -L $(DIR_LIB) -lftprintf -lft

compile_libs:
	make -C ./libft

%.o: %.c compile_libs $(HEADERS)
		gcc $(FLAGS) -o $@ -c $< -L $(DIR_LIB) -lft -lftprintf

clean:
	make -C ./libft/ $@
	/bin/rm -f $(OBJECT_POW)

fclean: clean
	make -C ./libft/ $@
	rm -f $(NAME)

re:		fclean all
