/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 14:26:47 by ahonchar          #+#    #+#             */
/*   Updated: 2018/06/22 14:26:49 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_stat			**read_current(char *path)
{
	t_stat	**list;

	ft_strcpy(path, ".");
	list = malloc_list(1);
	get_data(".", ".", list, 0);
	return (list);
}

static t_stat	**malloc_argc(char **av, t_flag *flags, int i)
{
	int		j;
	t_stat	**list;

	j = i;
	while (av[i])
		i++;
	if (!(list = malloc_list(i - j)))
		perror("Error:");
	i = 0;
	while (av[j])
	{
		if (!(get_data(av[j], av[j], list, i)))
			ft_printf("ft_ls: %s: %s\n", av[j], strerror(errno));
		j++;
		i++;
	}
	if (i > 1)
		flags->r_mode = 1;
	return (list);
}

static t_stat	**read_args(char **av, t_flag *flags, char *path)
{
	int		i;

	i = 0;
	while (av[++i] && av[i][0] == '-' && av[i][1])
	{
		if ((ft_strcmp(av[i], "--") == 0) && i++)
			break ;
		parse_flags(flags, av[i]);
	}
	if (!av[i])
		return (read_current(path));
	return (malloc_argc(av, flags, i));
}

int				main(int ac, char **av)
{
	char	*path;
	t_stat	**list;
	t_flag	*flags;
	_Bool	argc;

	argc = 0;
	flags = init_flags();
	path = ft_strnew(PATH_MAX);
	if (ac < 2)
		list = read_current(path);
	else
	{
		list = read_args(av, flags, path);
		argc = 1;
	}
	out_result(list, flags, path, argc);
	free_list(list);
	free(flags);
	free(path);
	system("leaks -quiet ft_ls");
	return (0);
}
