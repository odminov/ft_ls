/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
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
	while (list && *list)
	{
		ft_printf("%s %3u %s %5s %6lld date  time   %s\n",
			(*list)->perm, (*list)->nlink, (*list)->user, (*list)->group, (*list)->size, (*list)->fname);
		list++;
	}
}

void	print_short_list(t_stat **list)
{
	while (list && *list)
	{
		ft_printf("%s\n", (*list)->fname);
		list++;
	}
}

int		main(int ac, char **av)
{
	char	path[PATH_MAX];
	t_stat	**list;
	t_flag	*flags;
	int		i;
	int		j;

	list = NULL;
	flags = init_flags();
	if (ac < 2)
		ft_strcpy(path, ".");
	else
	{
		i = 1;
		while (av[i] && av[i][0] == '-')
		{
			if (!ft_strcmp(av[i], "--"))
			{
				i++;
				break ;
			}
			parse_flags(flags, av[i]);
			i++;
		}
		if (!av[i])
			ft_strcpy(path, ".");
		else
		{
			j = i;
			while (av[i])
				i++;
			list = malloc_list(i - j);
			i = 0;
			while (av[j])
			{
				get_data(av[j], av[j], list, i);
				i++;
				j++;
			}
		}
	}
	// if (ft_strcmp(path, "/"))
	// 	ft_strcat(path, "/");
	// list = read_dir(path, flags);
	if (flags->l)
		print_long_list(list);
	else
		print_short_list(list);
	// if (_DARWIN_FEATURE_64_BIT_INODE)
	// 	ft_printf("set darwin\n");
	// else
	// 	ft_printf("not set darwin\n");
	// my_free(list);
	system("leaks -quiet ft_ls");
	return (0);
}
