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

SRC_POW = main.c read_dir.c time.c permissions.c create_list.c flags.c lengths.c out_res.c free.c sort.c
OBJECT_POW = $(SRC_POW:.c=.o)

DIR_LIB = ./libft

all: $(NAME)

$(NAME): $(OBJECT_POW)
	make -C ./libft
	gcc -o $(NAME) $(FLAGS) $(OBJECT_POW) -L $(DIR_LIB) -lft -lftprintf
	@printf "\x1b[32m%s compiled\n\x1b[0m\n" $(NAME)

%.o: %.c $(HEADERS)
	gcc $(FLAGS) -o $@ -c $<

clean:
	make -C ./libft/ $@
	rm -f $(OBJECT_POW)

fclean: clean
	make -C ./libft/ $@
	rm -f $(NAME)

re:		fclean all
