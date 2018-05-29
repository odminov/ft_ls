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
#include <sys/stat.h>

char	*parse_chmod(mode_t mode)
{
	int		i;
	char	*chmod;

	i = 0;
	if (!(chmod = (char *)malloc(21)))
		exit(1);
	chmod[i++] = (S_ISDIR(mode)) ? 'd' : '-';
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
