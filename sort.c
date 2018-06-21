/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 17:40:37 by ahonchar          #+#    #+#             */
/*   Updated: 2018/06/12 17:40:38 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#define NAME list[j]->fname
#define NXT_NAME list[j + 1]->fname

static void	swap_pointers(t_stat *a, t_stat *b)
{
	t_stat	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static void	sort_time(t_stat **list, t_flag *flags, int j)
{
	if (!flags->r && list[j + 1] && (list[j]->time < list[j + 1]->time))
		swap_pointers(list[j], list[j + 1]);
	else if (!flags->r && list[j + 1] && (list[j]->time == list[j + 1]->time))
	{
		if (ft_strcmp(NAME, NXT_NAME) > 0)
			swap_pointers(list[j], list[j + 1]);
	}
	if (flags->r && list[j + 1] && (list[j]->time > list[j + 1]->time))
		swap_pointers(list[j], list[j + 1]);
	else if (flags->r && list[j + 1] && (list[j]->time == list[j + 1]->time))
	{
		if (ft_strcmp(NAME, NXT_NAME) < 0)
			swap_pointers(list[j], list[j + 1]);
	}
}

static void	sort_name(t_stat **list, t_flag *flags, int j)
{
	if (!flags->r && NAME && NXT_NAME && (ft_strcmp(NAME, NXT_NAME) > 0))
		swap_pointers(list[j], list[j + 1]);
	if (flags->r && NAME && NXT_NAME && (ft_strcmp(NAME, NXT_NAME) < 0))
		swap_pointers(list[j], list[j + 1]);
}

void		buble_sort(t_stat **list, t_flag *flags)
{
	int		i;
	int		j;
	int		size;

	size = 0;
	while (list && list[size])
		size++;
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size - 1)
		{
			if (flags->t)
				sort_time(list, flags, j);
			else
				sort_name(list, flags, j);
		}
	}
}
