/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 14:41:37 by ahonchar          #+#    #+#             */
/*   Updated: 2018/05/29 14:41:39 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				contain(const char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (str[i]);
		i++;
	}
	return (0);
}

static t_flag	*init_flags(void)
{
	t_flag	*tmp;

	if (!(tmp = (t_flag *)malloc(sizeof(t_flag))))
		exit(1);
	tmp->a = 0;
	tmp->R = 0;
	tmp->r = 0;
	tmp->t = 0;
	tmp->l = 0;
	return (tmp);
}

t_flag			*parse_flags(char *arg)
{
	t_flag *tmp;

	tmp = init_flags();
	if (contain(arg, 'a'))
		tmp->a = 1;
	if (contain(arg, 'R'))
		tmp->R = 1;
	if (contain(arg, 'r'))
		tmp->r = 1;
	if (contain(arg, 't'))
		tmp->t = 1;
	if (contain(arg, 'l'))
		tmp->l = 1;
	return (tmp);
}
