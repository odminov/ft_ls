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

void	my_free(t_stat **list)
{
	int i;

	i = 0;
	if (list)
	{
		while (list[i])
		{
			if (list[i]->user)
				free(list[i]->user);
			if (list[i]->group)
				free(list[i]->group);
			if (list[i]->fname)
				free(list[i]->fname);
			free(list[i]);
			i++;
		}
		free(list);
	}
}

void	print_non_rec(t_stat **list, char mode)
{
	char	*temp;
	char	*time;

	while (list && *list)
	{
		temp = parse_perm((*list)->perm);
		time = parse_time((*list)->time);
		if (mode == 'l')
		{
			ft_printf("%s %3u %s %5s %6lld %s %s\n",
				temp, (*list)->nlink, (*list)->user, (*list)->group, (*list)->size, time, (*list)->fname);
		}
		else
		{
			if ((*list)->fname)
				ft_printf("%s\n", (*list)->fname);
		}
		free(temp);
		free(time);
		list++;
	}
}

long long	add_total(t_stat **list)
{
	long long	total;

	total = 0;
	while (list && *list)
	{
		total += (*list)->total;
		list++;
	}
	return (total);
}

void	sort_print_long(t_stat **list, t_flag *flags, char *path)
{
	t_stat	**dir;
	char	temp[PATH_MAX];
	char	*perm;
	char	*time;

	while (list && *list)
	{
		if ((*list)->fname)
		{
			ft_strcpy(temp, path);
			ft_strcat(path, (*list)->fname);
			perm = parse_perm((*list)->perm);
			time = parse_time((*list)->time);
			ft_printf("%s %3u %s %5s %lld %s %s\n",
				perm, (*list)->nlink, (*list)->user, (*list)->group, (*list)->size, time, (*list)->fname);
			free(perm);
			free(time);
			if (S_ISDIR((*list)->perm) || (S_ISLNK((*list)->perm) && path[ft_strlen(path) - 2] == '/'))
			{
				ft_strcmp((*list)->fname, "/") ? ft_strcat(path, "/") : 0;
				dir = read_dir(path, flags);
				if (flags->r_mode)
					ft_printf("\n%.*s:\n", (int)(ft_strlen(path) - 1), path);
				if (!dir)
					ft_printf("ft_ls: %s: Permission denied\n", (*list)->fname);
				(dir && *dir) ? ft_printf("total %lld\n", add_total(dir)) : 0;
				if (!flags->R)
					print_non_rec(dir, 'l');
				else
					sort_print_long(dir, flags, path);
				my_free(dir);
			}
			ft_strcpy(path, temp);
		}
		list++;
	}
}

void	sort_print(t_stat **list, t_flag *flags, char *path)
{
	t_stat	**dir;
	char	temp[PATH_MAX];

	while (list && *list)
	{
		if ((*list)->fname)
		{
			ft_strcpy(temp, path);
			ft_strcat(path, (*list)->fname);
			if (S_ISDIR((*list)->perm) || S_ISLNK((*list)->perm))
			{
				ft_strcmp((*list)->fname, "/") ? ft_strcat(path, "/") : 0;
				dir = read_dir(path, flags);
				if (flags->r_mode)
					ft_printf("\n%.*s:\n", (int)(ft_strlen(path) - 1), path);
				if (!dir)
					ft_printf("ft_ls: %s: Permission denied\n", (*list)->fname);
				if (flags->R)
					sort_print(dir, flags, path);
				else
					print_non_rec(dir, 'm');
				my_free(dir);
			}
			else
				ft_printf("%s\n", (*list)->fname);
			ft_strcpy(path, temp);
		}
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
	{
		ft_strcpy(path, "./");
		list = malloc_list(1);
		get_data(".", "./", list, 0);
	}
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
		{
			ft_strcpy(path, "./");
			list = malloc_list(1);
			get_data(".", "./", list, 0);
		}
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
			if (i > 1)
				flags->r_mode = 1;
		}
	}
	if (flags->l)
		sort_print_long(list, flags, path);
	else
		sort_print(list, flags, path);
/*	if (_DARWIN_FEATURE_64_BIT_INODE)
		ft_printf("set darwin\n");
	else
		ft_printf("not set darwin\n");
	my_free(list); */
	// system("leaks -quiet ft_ls");
	return (0);
}
