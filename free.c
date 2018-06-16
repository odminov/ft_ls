/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 18:07:31 by ahonchar          #+#    #+#             */
/*   Updated: 2018/06/10 18:08:03 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_list(t_stat **list)
{
	int i;

	i = 0;
	if (list)
	{
		while (list[i])
		{
			if (list[i]->fname)
				free(list[i]->fname);
			if (list[i]->group)
				free(list[i]->group);
			if (list[i]->user)
				free(list[i]->user);
			free(list[i]);
			i++;
		}
		free(list);
	}
}
