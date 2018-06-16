/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_and_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 18:01:51 by ahonchar          #+#    #+#             */
/*   Updated: 2018/06/10 18:01:52 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#define OUT_FORMAT "%-11s %*u %-*s  %-*s %*lld %-s %-s\n"
#define OUT_ARGS perm, width[0], (*list)->nlink, width[1], (*list)->user, width[2], (*list)->group, width[3], (*list)->size, time, (*list)->fname
#define OUT_ARGS_CURR perm, width[0], list->nlink, width[1], list->user, width[2], list->group, width[3], list->size, time, list->fname

static long long	add_total(t_stat **list)
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

static void			print_dir(t_stat **list, t_flag *flags, int *width)
{
	char	*time;
	char	*perm;

	if (flags->l)
		ft_printf("total %lld\n", add_total(list));
	buble_sort(list, flags);
	while (list && *list)
	{
		if ((*list)->fname)
		{
			time = parse_time((*list)->time);
			perm = parse_perm((*list)->perm);
			if (flags->l)
				ft_printf(OUT_FORMAT, OUT_ARGS);
			else
				ft_printf("%s\n", (*list)->fname);
			free(time);
			free(perm);
		}
		list++;
	}
}

void			sort_and_out(t_stat *list, t_flag *flags, char *path, int *width)
{
	t_stat	**dir;
	t_stat	**head;
	char	*perm;
	char	*time;
	char	*temp;

	(!*path) ? ft_strcat(path, list->fname) : 0;
	temp = ft_strdup(path);
	if (S_ISLNK(list->perm) && flags->l && path[ft_strlen(path) - 2] != '/')
	{
		time = parse_time(list->time);
		perm = parse_perm(list->perm);
		ft_printf(OUT_FORMAT, OUT_ARGS_CURR);
		free(time);
		free(perm);
		return ;
	}
	dir = read_dir(path, flags);
	head = dir;
	if (flags->r_mode)
		ft_printf("%s:\n", path);
	if (!dir)
		ft_printf("out res ft_ls: %s: %s\n", path, strerror(errno));
	width[0] = len_nlink(dir);
	width[1] = len_user(dir);
	width[2] = len_group(dir);
	width[3] = len_size(dir);
	print_dir(dir, flags, width);
	while (flags->R && dir && *dir)
	{
		(temp[ft_strlen(temp) - 1] != '/') ? ft_strcat(temp, "/") : 0;
		if ((*dir)->fname && S_ISDIR((*dir)->perm))
			sort_and_out(*dir, flags, ft_strcat(temp, (*dir)->fname), width);
		dir++;
		ft_strcpy(temp, path);
	}
	free(temp);
	if (head)
		free_list(head);
}

void	out_files(t_stat **list, t_flag *flags, int width[4])
{
	char	*perm;
	char	*time;

	while (list && *list)
	{
		if ((*list)->fname)
			if (!S_ISDIR((*list)->perm) && !S_ISLNK((*list)->perm))
			{
				time = parse_time((*list)->time);
				perm = parse_perm((*list)->perm);
				if (flags->l)
					ft_printf(OUT_FORMAT, OUT_ARGS);
				else
					ft_printf("%s\n", (*list)->fname);
				free(time);
				free(perm);
			}
		list++;
	}
	ft_printf("\n");
}

void	out_result(t_stat **list, t_flag *flags, char *path, _Bool argc_mode)
{
	int		*width;

	width = (int *)malloc(sizeof(int) * 4);
	width[0] = len_nlink(list);
	width[1] = len_user(list);
	width[2] = len_group(list);
	width[3] = len_size(list);
	buble_sort(list, flags);
	if (argc_mode)
		out_files(list, flags, width);
	while (list && *list)
	{
		if ((*list)->fname)
		{
			if (S_ISDIR((*list)->perm) || S_ISLNK((*list)->perm))
				sort_and_out(*list, flags, ft_strcpy(path, (*list)->fname), width);
		}
		list++;
		if (flags->r_mode && list && *list && (*list)->fname)
			ft_printf("\n");
	}
	free(width);
}
