/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 12:10:09 by ahonchar          #+#    #+#             */
/*   Updated: 2017/12/16 22:37:41 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static unsigned int		cnt_wrd(char const *s, char c)
{
	unsigned int	i;
	unsigned int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i])
				i++;
			words++;
		}
		else
			i++;
	}
	return (words);
}

static char				**copy_arr(char const *s, char **dst, char c)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	i = 0;
	j = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i])
			{
				dst[j][k] = (char)s[i];
				i++;
				k++;
			}
			dst[j++][k] = '\0';
			k = 0;
		}
		else
			i++;
	}
	dst[j] = NULL;
	return (dst);
}

static char				**check_and_malloc(char const *s, char c)
{
	char	**ret;

	if (!s)
		return (NULL);
	ret = (char **)malloc(sizeof(ret) * (cnt_wrd(s, c) + 1));
	if (!ret)
		return (NULL);
	return (ret);
}

static char				**my_free(char **s, int i)
{
	while (i >= 0)
		free(s[i--]);
	free(s);
	return (NULL);
}

char					**ft_strsplit(char const *s, char c)
{
	int				i;
	unsigned int	j;
	unsigned int	words;
	char			**ret;

	i = -1;
	j = 0;
	words = 0;
	ret = check_and_malloc(s, c);
	if (!ret)
		return (NULL);
	while (s[++i])
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i++])
				j++;
			words++;
			if (!(ret[words - 1] = (char *)malloc(j + 1)))
				if (!my_free(ret, words - 1))
					return (NULL);
			j = 0;
		}
	}
	return (copy_arr(s, ret, c));
}
