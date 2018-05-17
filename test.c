/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <ahonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 13:06:55 by ahonchar          #+#    #+#             */
/*   Updated: 2018/05/17 16:54:32 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>
#include "done/libft/libft.h"

char	*parse_time(char *time)
{
	int i;
	int j;
	char *buf;

	if (!(buf = (char *)malloc(30)))
		return (NULL);
	// printf("tisme: %c\n", time[4]);
	i = -1;
	j = 0;
	while (time[++i])
	{
		if (i < 4 || i > 15)
			continue;
		buf[j++] = time[i];
	}
	buf[j] = '\0';
	return (buf);
}

void	parse_chmod(char chmod[], mode_t mode)
{
	int i;

	i = 0;
	chmod[i++] = (S_ISDIR(mode)) ? 'd' : '-';
	chmod[i++] = ( (mode & S_IRUSR) ? 'r' : '-');
	chmod[i++] = ( (mode & S_IWUSR) ? 'w' : '-');
	chmod[i++] = ( (mode & S_IXUSR) ? 'x' : '-');
	chmod[i++] = ( (mode & S_IRGRP) ? 'r' : '-');
	chmod[i++] = ( (mode & S_IWGRP) ? 'w' : '-');
	chmod[i++] = ( (mode & S_IXGRP) ? 'x' : '-');
	chmod[i++] = ( (mode & S_IROTH) ? 'r' : '-');
	chmod[i++] = ( (mode & S_IWOTH) ? 'w' : '-');
	chmod[i++] = ( (mode & S_IXOTH) ? 'x' : '-');
	chmod[i] = '\0';
}

int		main(int ac, char **av)
{
	int				errno;
	DIR				*dir;
	struct dirent	*entry;
	struct stat		buf;
	struct passwd	*pass;
	struct group	*grp;
	char			*time;
	char			chmod[12];
	char			path[2048];
	char			current[1024];
	unsigned		blocks;

	if (ac != 2)
	{
		errno = EINVAL;
		perror(av[0]);
		exit(1);
	}
	if (_DARWIN_FEATURE_64_BIT_INODE)
		printf("set darwin\n");
	else
		printf("not set darwin\n");
	dir = opendir(av[1]);
	if (!dir)
	{
		perror("diropen");
		exit(1);
	}
	blocks = 0;
	ft_strcpy(path, av[1]);
	while ((entry = readdir(dir)) != NULL)
	{
		// printf("%s\n", strcat(str, entry->d_name));
		strcpy(current, ft_strcat(path, entry->d_name));
		lstat(current, &buf);
		if (entry->d_name[0] == '.')
			continue;
		blocks += buf.st_blocks;
		if (!(pass = getpwuid(buf.st_uid)))
		{
			perror("Bad uid");
			exit(1);
		}
		if (!(grp = getgrgid(buf.st_gid)))
		{
			perror("Bad uid");
			exit(1);
		}
		time = ctime(&buf.st_mtimespec.tv_sec);
		if (!(time = parse_time(time)))
		{
			errno = ENOMEM;
			perror(av[0]);
			exit(1);
		}
		parse_chmod(chmod, buf.st_mode);
		printf("%s %2u %s %5s %5lld %s %s\n", chmod, buf.st_nlink, pass->pw_name, grp->gr_name, buf.st_size, time, entry->d_name);
		ft_strcpy(path, av[1]);
	}
	printf("total %u\n", blocks);
	closedir(dir);
	return (0);
}
