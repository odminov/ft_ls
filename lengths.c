/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lengths.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 20:59:22 by ahonchar          #+#    #+#             */
/*   Updated: 2018/06/08 20:59:25 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		len_nlink(t_stat **list)
{
	int		longest;
	int		len;
	char	*temp;

	longest = 0;
	while (list && *list)
	{
		temp = ft_itoa(((*list)->nlink));
		if ((len = (int)ft_strlen(temp)) > longest)
			longest = len;
		free(temp);
		list++;
	}
	return (longest);
}

int		len_user(t_stat **list)
{
	int		longest;
	int		len;

	longest = 0;
	while (list && *list)
	{
		if ((len = (int)ft_strlen((*list)->user)) > longest)
			longest = len;
		list++;
	}
	return (longest);
}

int		len_group(t_stat **list)
{
	int		longest;
	int		len;

	longest = 0;
	while (list && *list)
	{
		if ((len = (int)ft_strlen((*list)->group)) > longest)
			longest = len;
		list++;
	}
	return (longest);
}

int		len_size(t_stat **list)
{
	int			longest;
	int			len;
	char		*temp;
	long long	size;

	longest = 0;
	while (list && *list)
	{
		size = (*list)->size;
		temp = ft_itoa_long(&size, 's');
		if ((len = (int)ft_strlen(temp)) > longest)
			longest = len;
		list++;
		free(temp);
	}
	return (longest);
}
