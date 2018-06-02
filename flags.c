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

t_flag	*init_flags(void)
{
	t_flag	*tmp;

	if (!(tmp = (t_flag *)malloc(sizeof(t_flag))))
	{
		perror("error:");
		exit(1);
	}
	tmp->a = 0;
	tmp->R = 0;
	tmp->r = 0;
	tmp->r_mode = 0;
	tmp->t = 0;
	tmp->l = 0;
	return (tmp);
}

void	parse_flags(t_flag *flags, char *arg)
{
	int i;

	i = 0;
	while (arg[++i])
	{
		if (arg[i] == 'a')
			flags->a = 1;
		else if (arg[i] == 'R')
		{
			flags->R = 1;
			flags->r_mode = 1;
		}
		else if (arg[i] == 'r')
			flags->r = 1;
		else if (arg[i] == 't')
			flags->t = 1;
		else if (arg[i] == 'l')
			flags->l = 1;
		else
		{
			ft_printf("\
ft_ls: illegal option -- %c\nusage: ft_ls [-Rlart] [file ...]\n", arg[i]);
			exit(1);
		}
	}
}
