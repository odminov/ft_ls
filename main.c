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

void	print_long_list(t_stat **list)
{
	while (*list)
	{
		ft_printf("%s %3u %s %5s %6lld date  time   %s\n",
			(*list)->perm, (*list)->nlink, (*list)->user, (*list)->group, (*list)->size, (*list)->fname);
		list++;
	}
}

void	print_short_list(t_stat **list)
{
	while (*list)
	{
		ft_printf("%s\n", (*list)->fname);
		list++;
	}
}

int		main(int ac, char **av)
{
	int		errno;
	char	*path;
	t_stat	**list;
	t_flag	*flags;

	// if (ac <= 2)
	// {
	// 	errno = EINVAL;
	// 	perror(av[0]);
	// 	exit(1);
	// }
	if (ac > 1 && av[1][0] == '-')
		flags = parse_flags(av[1]);
	else
		flags = parse_flags(" ");
	if (ac == 3)
		path = ft_strdup(av[2]);
	else if (ac == 2 && av[1][0] != '-')
		path = ft_strdup(av[1]);
	else
		path = ft_strdup(".");
	if (ft_strcmp(path, "/"))
		ft_strcat(path, "/");
	list = read_dir(path, flags);
	if (flags->l)
		print_long_list(list);
	else
		print_short_list(list);
	// if (_DARWIN_FEATURE_64_BIT_INODE)
	// 	ft_printf("set darwin\n");
	// else
	// 	ft_printf("not set darwin\n");
	// my_free(list);
	free(path);
	system("leaks -quiet ft_ls");
	return (0);
}
