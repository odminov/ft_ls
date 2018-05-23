/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 17:37:53 by ahonchar          #+#    #+#             */
/*   Updated: 2018/05/23 18:02:01 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# define FLAGS "ABCFGHLOPRSTUW@abcdefghiklmnopqrstuwx1"
# include <errno.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct	s_stat
{
	char		*perm;
	char		*user;
	char		*group;
	unsigned	time;
	char		*fname;
	unsigned	nlink;
	long long	size;
	long long	blocks;
}				t_stat;

void			read_dir(char **av);
char			*parse_chmod(mode_t mode);
t_stat			**create_list(char *path);

#endif
