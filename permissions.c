/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permissions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 13:22:27 by ahonchar          #+#    #+#             */
/*   Updated: 2018/06/22 13:22:39 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	check_type(mode_t mode, char *chmod)
{
	if (S_ISDIR(mode))
		*chmod = 'd';
	else if (S_ISLNK(mode))
		*chmod = 'l';
	else if (S_ISBLK(mode))
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

static void	chmod_user(mode_t mode, char *chmod)
{
	chmod[1] = ((mode & S_IRUSR) ? 'r' : '-');
	chmod[2] = ((mode & S_IWUSR) ? 'w' : '-');
	if ((mode & S_ISUID) && (mode & S_IXUSR))
		chmod[3] = 's';
	else if ((mode & S_ISUID) && !(mode & S_IXUSR))
		chmod[3] = 'S';
	else if ((mode & S_IXUSR))
		chmod[3] = 'x';
	else
		chmod[3] = '-';
}

static void	chmod_group(mode_t mode, char *chmod)
{
	chmod[4] = ((mode & S_IRGRP) ? 'r' : '-');
	chmod[5] = ((mode & S_IWGRP) ? 'w' : '-');
	if ((mode & S_ISGID) && (mode & S_IXGRP))
		chmod[6] = 's';
	else if ((mode & S_ISGID) && !(mode & S_IXGRP))
		chmod[6] = 'S';
	else if ((mode & S_IXGRP))
		chmod[6] = 'x';
	else
		chmod[6] = '-';
}

static void	chmod_other(mode_t mode, char *chmod)
{
	chmod[7] = ((mode & S_IROTH) ? 'r' : '-');
	chmod[8] = ((mode & S_IWOTH) ? 'w' : '-');
	if ((mode & S_ISVTX) && (mode & S_IXOTH))
		chmod[9] = 't';
	else if ((mode & S_ISVTX) && !(mode & S_IXOTH))
		chmod[9] = 'T';
	else if ((mode & S_IXOTH))
		chmod[9] = 'x';
	else
		chmod[9] = '-';
}

char		*parse_perm(mode_t mode)
{
	char	*chmod;

	if (!(chmod = (char *)malloc(21)))
		exit(1);
	check_type(mode, chmod);
	chmod_user(mode, chmod);
	chmod_group(mode, chmod);
	chmod_other(mode, chmod);
	chmod[10] = '\0';
	return (chmod);
}
