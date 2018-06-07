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
	temp->perm = 0;
	temp->user = NULL;
	temp->group = NULL;
	temp->fname = NULL;
	temp->size = 0;
	temp->total = 0;
	temp->nlink = 0;
	return (temp);
}

t_stat			**malloc_list(int elements)
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

// static	char	*path_error(char *path)
// {
// 	char	*res;
// 	int		i;
// 	int		j;
// 	_Bool	end;

// 	res = (char *)malloc(PATH_MAX + 1);
// 	i = 0;
// 	while (path[i])
// 		i++;
// 	j = 0;
// 	end = 0;
// 	while (--i >= 0)
// 	{
// 		if (path[i] == '/')
// 		{
// 			if (end)
// 				break ;
// 			end = 1;
// 			continue;
// 		}
// 		res[j] = path[i];
// 		j++;
// 	}
// 	res[j] = '\0';
// 	return (res);
// }

t_stat			**create_list(char *path, t_flag *flags)
{
	DIR				*dir;
	int				elements;
	struct dirent	*entry;
	// char			*temp;

	dir = opendir(path);
	if (!dir)
	{
		// temp = path_error(path);
		// ft_strrev(temp);
		// ft_printf("ft_ls: %s: ", temp);
		// free(temp);
		// perror("");
		return (NULL);
	}
	elements = 0;
	while ((entry = readdir(dir)))
	{
		if (!flags->a && entry->d_name[0] == '.')
			continue;
		elements++;
	}
	closedir(dir);
	return (malloc_list(elements));
}
