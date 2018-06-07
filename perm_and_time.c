/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_permissions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 23:04:06 by ahonchar          #+#    #+#             */
/*   Updated: 2018/05/23 23:04:10 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <time.h>
#define HALF_YEAR 15768000
#define HALF_YEAR_BIS 15811200
#define IS_BISSEXTILE(i) (i % 4 == 0 ? 1 : 0)

static	void	check_type(mode_t mode, char *chmod)
{
	if (S_ISDIR(mode))
		*chmod = 'd';
	else if (S_ISLNK(mode))
		*chmod = 'l';
	else if	(S_ISBLK(mode))
		*chmod = 'b';
	else if (S_ISCHR(mode))
		*chmod = 'c';
	else if (S_ISSOCK(mode))
		*chmod = 's';
	else if (S_ISFIFO(mode))
		*chmod = 'p';
	else
		*chmod = '-';
}

char	*parse_perm(mode_t mode)
{
	int		i;
	char	*chmod;

	if (!(chmod = (char *)malloc(21)))
		exit(1);
	check_type(mode, chmod);
	i = 1;
	chmod[i++] = ((mode & S_IRUSR) ? 'r' : '-');
	chmod[i++] = ((mode & S_IWUSR) ? 'w' : '-');
	chmod[i++] = ((mode & S_IXUSR) ? 'x' : '-');
	chmod[i++] = ((mode & S_IRGRP) ? 'r' : '-');
	chmod[i++] = ((mode & S_IWGRP) ? 'w' : '-');
	chmod[i++] = ((mode & S_IXGRP) ? 'x' : '-');
	chmod[i++] = ((mode & S_IROTH) ? 'r' : '-');
	chmod[i++] = ((mode & S_IWOTH) ? 'w' : '-');
	chmod[i++] = ((mode & S_IXOTH) ? 'x' : '-');
	chmod[i] = '\0';
	return (chmod);
}

static char	*write_year(time_t mtime)
{
	char	*temp;
	char	*res;
	char	*temp2;

	temp = ft_strdup(ctime(&mtime));
	temp[24] = '\0';
	res = ft_strdup(temp + 4);
	temp2 = res;
	res[6] = '\0';
	res = ft_strjoin(res, (temp + (ft_strlen(temp) - 5)));
	free(temp2);
	free(temp);
	return (res);
}

static char	*write_time(time_t mtime)
{
	char	*temp;
	char	*res;

	temp = ft_strdup(ctime(&mtime));
	temp[16] = '\0';
	res = ft_strdup(temp + 4);
	free(temp);
	return (res);
}

char	*parse_time(time_t mtime)
{
	time_t	curr_time;
	int		curr_year;
	char	*res;
	char	*temp;

	curr_time = time(&curr_time);
	temp = ft_strdup(ctime(&curr_time));
	curr_year = ft_atoi(temp + (ft_strlen(temp) - 5));
	if (IS_BISSEXTILE(curr_year))
	{
		if (curr_time - mtime > HALF_YEAR_BIS)
			res = write_year(mtime);
		else
			res = write_time(mtime);
	}
	else
	{
		if (curr_time - mtime > HALF_YEAR)
			res = write_year(mtime);
		else
			res = write_time(mtime);
	}
	free(temp);
	return (res);
}
