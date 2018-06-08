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

t_stat	**read_current(char *path)
{
	t_stat	**list;

	ft_strcpy(path, ".");
	list = malloc_list(1);
	get_data(".", ".", list, 0);
	return (list);
}

void	print_dir(t_stat **list, t_flag *flags, int width[4])
{
	char	*time;
	char	*perm;

	if (flags->l)
		ft_printf("total %lld\n", add_total(list));
	while (list && *list)
	{
		if ((*list)->fname)
		{
			time = parse_time((*list)->time);
			perm = parse_perm((*list)->perm);
			if (flags->l)
			{
				ft_printf("%s %*u %*s %*s %*lld %s %s\n",
					perm, width[0], (*list)->nlink, width[1], (*list)->user, width[2], (*list)->group, width[3], (*list)->size, time, (*list)->fname);
			}
			else
				ft_printf("%s\n", (*list)->fname);
			free(time);
			free(perm);
		}
		list++;
	}
}

void	sort_and_out(t_stat *list, t_flag *flags, char *path, int width[4])
{
	t_stat	**dir;
	t_stat	**temp;
	char	*perm;
	char	*time;

	(!*path) ? ft_strcat(path, list->fname) : 0;
	if (S_ISLNK(list->perm) && flags->l && path[ft_strlen(path) - 2] != '/')
	{
		time = parse_time(list->time);
		perm = parse_perm(list->perm);
		ft_printf("%s %*u %*s %*s %*lld %s %s\n",
					perm, width[0], list->nlink, width[1], list->user, width[2], list->group, width[3], list->size, time, list->fname);
		free(time);
		free(perm);
		return ;
	}
	dir = read_dir(path, flags);
	if (flags->r_mode)
		ft_printf("\n%s:\n", path);
	if (!dir)
		ft_printf("ft_ls: %s: Permission denied\n", list->fname);
	temp = dir;
	width[0] = len_nlink(dir);
	width[1] = len_user(dir);
	width[2] = len_group(dir);
	width[3] = len_size(dir);
	dir = temp;
	print_dir(dir, flags, width);
	my_free(dir);
}

void	print_args(t_stat **list, t_flag *flags)
{
	char	*path;
	t_stat	**temp;
	int		width[4];

	path = ft_strnew(PATH_MAX);
	temp = list;
	while (list && *list)
	{
		if ((*list)->fname)
			if (!S_ISDIR((*list)->perm) && !S_ISLNK((*list)->perm))
				ft_printf("%s\n", (*list)->fname);
		list++;
	}
	list = temp;
	width[0] = len_nlink(list);
	width[1] = len_user(list);
	width[2] = len_group(list);
	width[3] = len_size(list);
	list = temp;
	while (list && *list)
	{
		if ((*list)->fname)
			if (S_ISDIR((*list)->perm) || S_ISLNK((*list)->perm))
				sort_and_out(*list, flags, ft_strcpy(path, (*list)->fname), width);
		list++;
	}
	free(path);
}

int		main(int ac, char **av)
{
	char	*path;
	t_stat	**list;
	t_flag	*flags;
	int		i;
	int		j;

	list = NULL;
	flags = init_flags();
	path = ft_strnew(PATH_MAX);
	if (ac < 2)
		list = read_current(path);
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
		if (av[i])
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
			print_args(list, flags);
			free(path);
			system("leaks -quiet ft_ls");
			return (0);
		}
		else
			list = read_current(path);
	}
	// if (flags->l)
	// 	sort_print_long(list, flags, path);
	// else
	// 	sort_print(list, flags, path);
/*	if (_DARWIN_FEATURE_64_BIT_INODE)
		ft_printf("set darwin\n");
	else
		ft_printf("not set darwin\n");
	my_free(list); */
	free(path);
	system("leaks -quiet ft_ls");
	return (0);
}
