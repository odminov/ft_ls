/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 19:39:56 by ahonchar          #+#    #+#             */
/*   Updated: 2018/05/23 19:39:59 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	int		errno;
	char	*path;
	t_stat	**list;

	if (ac != 2)
	{
		errno = EINVAL;
		perror(av[0]);
		exit(1);
	}
	path = ft_strdup(av[1]);
	if (ft_strcmp(path, "/"))
		ft_strcat(path, "/");
	list = read_dir(path);
	print_list(list);
	// if (_DARWIN_FEATURE_64_BIT_INODE)
	// 	ft_printf("set darwin\n");
	// else
	// 	ft_printf("not set darwin\n");
	my_free(list);
	free(path);
	system("leaks -quiet ft_ls");
	return (0);
}
