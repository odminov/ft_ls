/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 23:05:49 by ahonchar          #+#    #+#             */
/*   Updated: 2018/05/23 23:05:52 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <dirent.h>

static t_stat	*init_list(void)
{
	t_stat	*temp;

	if (!(temp = (t_stat *)malloc(sizeof(t_stat))))
		return (NULL);
	temp->time = 0;
	temp->perm = NULL;
	temp->user = NULL;
	temp->group = NULL;
	temp->fname = NULL;
	temp->size = 0;
	temp->blocks = 0;
	temp->nlink = 0;
	return (temp);
}

static t_stat	**malloc_list(int elements)
{
	t_stat	**curr_dir;

	if (!(curr_dir = (t_stat **)malloc(sizeof(t_stat *) * (elements + 1))))
	{
		perror("ERROR");
		exit(1);
	}
	curr_dir[elements] = NULL;
	while (--elements >= 0)
		if (!(curr_dir[elements] = init_list()))
			exit(1);
	return (curr_dir);
}

t_stat			**create_list(char *path)
{
	DIR		*dir;
	int		elements;

	dir = opendir(path);
	if (!dir)
	{
		perror("diropen");
		exit(1);
	}
	elements = 0;
	while (readdir(dir) != NULL)
		elements++;
	closedir(dir);
	return (malloc_list(elements));
}
