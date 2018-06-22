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
#include <unistd.h>
#define OUT_FORMAT_STD "%-11s %*u %-*s  %-*s  %*lld %-s %-s\n"
#define OUT_FORMAT_LNK "%-11s %*u %-*s  %-*s  %*lld %-s %-s -> %s\n"
#define OUT_FORMAT_MAJ "%-11s %*u %-*s  %-*s  %*lld, %*u %-s %-s\n"
#define OUT_ARGS_STD perm, width[0], (*list)->nlink, width[1], (*list)->user, width[2], (*list)->group, (width[3] + width[4]), (*list)->size, time, (*list)->fname
#define OUT_ARGS_MAJ perm, width[0], (*list)->nlink, width[1], (*list)->user, width[2], (*list)->group, width[3], (*list)->size, width[4], (*list)->minor, time, (*list)->fname
#define OUT_ARGS_CURR_STD perm, width[0], list->nlink, width[1], list->user, width[2], list->group, (width[3] + width[4]), list->size, time, list->fname, buf

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

void	path_err(char *path)
{
	char	out[ft_strlen(path)];
	int		i;
	int		j;

	i = 0;
	while (path[i])
		i++;
	j = 0;
	while (i >= 0 && path[--i] != '/')
		out[j++] = path[i];
	out[j] = '\0';
	ft_strrev(out);
	ft_putstr(out);
}

void	read_lengths(int *width, t_stat **list)
{
	width[0] = len_nlink(list);
	width[1] = len_user(list);
	width[2] = len_group(list);
	width[3] = len_size(list);
	width[4] = len_minor(list);
}

static void			long_out(t_stat **list, char *path, int *width)
{	
	char	*time;
	char	*perm;
	char	buf[PATH_MAX + 1];
	int		len;

	time = parse_time((*list)->time);
	perm = parse_perm((*list)->perm);
	if (S_ISCHR((*list)->perm) || S_ISBLK((*list)->perm))
		ft_printf(OUT_FORMAT_MAJ, OUT_ARGS_MAJ);
	else
	{
		if (S_ISLNK((*list)->perm))
		{
			ft_strcpy(buf, path);
			ft_strcat(buf, "/");
			len = readlink(ft_strcat(buf, (*list)->fname), buf, PATH_MAX);
			buf[len] = '\0';
			ft_printf(OUT_FORMAT_LNK, OUT_ARGS_STD, buf);
		}
		else
			ft_printf(OUT_FORMAT_STD, OUT_ARGS_STD);
	}
	free(time);
	free(perm);
}

static void			print_dir(t_stat **list, t_flag *flags, int *width, char *path)
{
	if (flags->l && list && *list && (*list)->fname)
		ft_printf("total %lld\n", add_total(list));
	buble_sort(list, flags);
	while (list && *list)
	{
		if ((*list)->fname)
		{
			if (flags->l)
				long_out(list, path, width);
			else
				ft_printf("%s\n", (*list)->fname);			
		}
		list++;
	}
}

static void	out_link(t_stat *list, int *width)
{
	char	*time;
	char	*perm;
	char	buf[PATH_MAX + 1];
	int		len;

	time = parse_time(list->time);
	perm = parse_perm(list->perm);
	len = readlink(list->fname, buf, PATH_MAX);
	buf[len] = '\0';
	ft_printf(OUT_FORMAT_LNK, OUT_ARGS_CURR_STD);
	free(time);
	free(perm);
}

void			sort_and_out(t_stat *list, t_flag *flags, char *path, int *width)
{
	t_stat	**dir;
	t_stat	**head;
	char	*temp;

	(!*path) ? ft_strcat(path, list->fname) : 0;
	temp = ft_strnew(PATH_MAX);
	ft_strcpy(temp, path);
	if (S_ISLNK(list->perm) && flags->l && path[ft_strlen(path) - 2] != '/')
	{
		out_link(list, width);
		return ;
	}
	dir = read_dir(path, flags);
	head = dir;
	if (flags->r_mode)
		ft_printf("%s:\n", path);
	if (!dir)
	{
		ft_putstr("ft_ls: ");
		path_err(path);
		ft_printf(": %s\n", strerror(errno));
	}
	read_lengths(width, dir);
	print_dir(dir, flags, width, path);
	while (flags->rec && dir && *dir)
	{
		(temp[ft_strlen(temp) - 1] != '/') ? ft_strcat(temp, "/") : 0;
		if ((*dir)->fname && S_ISDIR((*dir)->perm) && ft_strcmp((*dir)->fname, ".")
		&& ft_strcmp((*dir)->fname, ".."))
		{
			ft_putstr("\n");
			sort_and_out(*dir, flags, ft_strcat(temp, (*dir)->fname), width);
		}
		dir++;
		ft_strcpy(temp, path);
	}
	free(temp);
	if (head)
		free_list(head);
}

void	out_files(t_stat **list, t_flag *flags, int *width, char *path)
{
	_Bool	dir;
	_Bool	files;

	dir = 0;
	files = 0;
	while (list && *list)
	{
		if ((*list)->fname)
		{
			if (!S_ISDIR((*list)->perm))
			{
				files = 1;
				if (flags->l)
					long_out(list, path, width);
				else
					if (!S_ISLNK((*list)->perm))
						ft_printf("%s\n", (*list)->fname);
			}
			else
				dir = 1;
		}
		list++;
	}
	if (dir && files)
		ft_putstr("\n");
}

static void	check_last(t_stat **temp)
{
	temp++;
	while (*temp)
	{
		if (S_ISDIR((*temp)->perm) || (S_ISLNK((*temp)->perm)))
		{
			ft_putstr("\n");
			break ;
		}
		temp++;
	}
}

void		out_result(t_stat **list, t_flag *flags, char *path, _Bool argc_mode)
{
	int		*width;

	width = (int *)malloc(sizeof(int) * 5);
	read_lengths(width, list);
	buble_sort(list, flags);
	if (argc_mode)
		out_files(list, flags, width, path);
	while (list && *list)
	{
		if ((*list)->fname)
		{
			if (S_ISDIR((*list)->perm) || (S_ISLNK((*list)->perm) && !flags->l))
			{
				sort_and_out(*list, flags, ft_strcpy(path, (*list)->fname), width);
				check_last(list);
				list++;
			}
		}
		list++;
	}
	free(width);
}
