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
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#define NAME entry->d_name

int		get_data(char *name, char *path, t_stat **curr_dir, int idx)
{
	struct stat		buf;
	struct passwd	*pass;
	struct group	*grp;

	if (lstat(path, &buf) < 0)
		return (0);
	if (!(pass = getpwuid(buf.st_uid)))
		return (0);
	if (!(grp = getgrgid(buf.st_gid)))
		return (0);
	curr_dir[idx]->time = buf.st_mtime;
	curr_dir[idx]->perm = buf.st_mode;
	curr_dir[idx]->user = ft_strdup(pass->pw_name);
	curr_dir[idx]->group = ft_strdup(grp->gr_name);
	curr_dir[idx]->fname = ft_strdup(name);
	curr_dir[idx]->size = buf.st_size;
	if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode))
	{
		curr_dir[idx]->size = major(buf.st_rdev);
		curr_dir[idx]->minor = minor(buf.st_rdev);
	}
	curr_dir[idx]->total = buf.st_blocks;
	curr_dir[idx]->nlink = buf.st_nlink;
	return (1);
}

t_stat	**read_dir(char *path, t_flag *flags)
{
	DIR				*dir;
	t_stat			**curr_dir;
	struct dirent	*entry;
	char			temp[PATH_MAX];
	int				i;

	ft_strcpy(temp, path);
	(temp[ft_strlen(temp) - 1] != '/') ? ft_strcat(temp, "/") : 0;
	if (!(curr_dir = create_list(path, flags)))
		return (NULL);
	if (!(dir = opendir(path)))
		return (NULL);
	i = 0;
	while ((entry = readdir(dir)) != NULL)
	{
		if (!flags->a && NAME[0] == '.')
			continue;
		(temp[ft_strlen(temp) - 1] != '/') ? ft_strcat(temp, "/") : 0;
		if (!(get_data(NAME, ft_strcat(temp, NAME), curr_dir, i)))
			return (NULL);
		ft_strcpy(temp, path);
		i++;
	}
	closedir(dir);
	return (curr_dir);
}
