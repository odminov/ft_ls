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
# include <errno.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <sys/stat.h>
# include "./libft/libft.h"
# include "./libft/ft_printf/ft_printf.h"

typedef struct	s_stat
{
	mode_t		perm;
	char		*user;
	char		*group;
	unsigned	time;
	char		*fname;
	unsigned	nlink;
	long long	size;
	unsigned	minor;
	long long	total;
}				t_stat;

typedef struct	s_flag
{
	_Bool		a;
	_Bool		l;
	_Bool		rec;
	_Bool		r_mode;
	_Bool		r;
	_Bool		t;
}				t_flag;

t_stat			**read_dir(char *path, t_flag *flags);
char			*parse_perm(mode_t mode);
t_stat			**create_list(char *path, t_flag *flags);
t_stat			**malloc_list(int elements);
int				contains(const char *str, char c);
t_flag			*init_flags(void);
void			parse_flags(t_flag *flags, char *arg);
int				get_data(char *name, char *path, t_stat **curr_dir, int idx);
char			*parse_time(time_t mtime);
int				len_nlink(t_stat **list);
int				len_user(t_stat **list);
int				len_group(t_stat **list);
int				len_size(t_stat **list);
int				len_minor(t_stat **list);
t_stat			**read_current(char *path);
void			out_result(t_stat **list, t_flag *flags,
							char *path, _Bool argc_mode);
void			free_list(t_stat **list);
void			buble_sort(t_stat **list, t_flag *flags);

#endif
