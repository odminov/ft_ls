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

	lstat(path, &buf);
	if (!(pass = getpwuid(buf.st_uid)))
	{
		perror("Bad user id");
		exit(1);
	}
	if (!(grp = getgrgid(buf.st_gid)))
	{
		perror("Bad group id");
		exit(1);
	}
	curr_dir[idx]->time = buf.st_mtimespec.tv_sec;
	curr_dir[idx]->perm = parse_chmod(buf.st_mode);
	curr_dir[idx]->user = ft_strdup(pass->pw_name);
	curr_dir[idx]->group = ft_strdup(grp->gr_name);
	curr_dir[idx]->fname = ft_strdup(name);
	curr_dir[idx]->size = buf.st_size;
	curr_dir[idx]->blocks += buf.st_block;
	curr_dir[idx]->nlink = buf.st_nlink;
}

t_stat	**read_dir(char *path)
{
	DIR				*dir;
	t_stat			**curr_dir;
	struct dirent	*entry;
	char			temp[2048];
	int				i;

	curr_dir = create_list(path);
	dir = opendir(path);
	if (!dir)
	{
		perror("diropen");
		exit(1);
	}
	ft_strcpy(temp, path);
	i = 0;
	while ((entry = readdir(dir)) != NULL)
	{
		get_data(entry->d_name, ft_strcat(temp, entry->d_name), curr_dir, i);
		ft_strcpy(temp, path);
		i++;
	}
	closedir(dir);
	return (curr_dir);
}
