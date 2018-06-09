/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 19:38:01 by ahonchar          #+#    #+#             */
/*   Updated: 2018/05/23 19:38:03 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void	get_data(char *name, char *path, t_stat **curr_dir, int idx)
{
	struct stat		buf;
	struct passwd	*pass;
	struct group	*grp;

	if (lstat(path, &buf) < 0)
	{
		ft_printf("ft_ls: %s: ", path);
		perror("");
		return ;
	}
	if (!(pass = getpwuid(buf.st_uid)))
		exit(1);
	if (!(grp = getgrgid(buf.st_gid)))
		exit(1);
	#ifdef _DARWIN_FEATURE_64_BIT_INODE
		curr_dir[idx]->time = buf.st_mtimespec.tv_sec;
	#endif
	#ifndef _DARWIN_FEATURE_64_BIT_INODE
		curr_dir[idx]->time = buf.st_mtime;
	#endif
	curr_dir[idx]->perm = buf.st_mode;
	curr_dir[idx]->user = ft_strdup(pass->pw_name);
	curr_dir[idx]->group = ft_strdup(grp->gr_name);
	curr_dir[idx]->fname = ft_strdup(name);
	curr_dir[idx]->size = buf.st_size;
	curr_dir[idx]->total = buf.st_blocks;
	curr_dir[idx]->nlink = buf.st_nlink;
}

t_stat	**read_dir(char *path, t_flag *flags)
{
	DIR				*dir;
	t_stat			**curr_dir;
	struct dirent	*entry;
	char			temp[PATH_MAX];
	int				i;

	curr_dir = create_list(path, flags);
	dir = opendir(path);
	if (!dir)
	{
		ft_printf("readdir path: %s\n", path);
		perror("readdir");
		return (NULL);
	}
	ft_strcpy(temp, path);
	i = 0;
	while ((entry = readdir(dir)) != NULL)
	{
		if (!flags->a && entry->d_name[0] == '.')
			continue;
		ft_strcmp(temp, "/") ? ft_strcat(temp, "/") : 0;
		get_data(entry->d_name, ft_strcat(temp, entry->d_name), curr_dir, i);
		ft_strcpy(temp, path);
		i++;
	}
	closedir(dir);
	return (curr_dir);
}
