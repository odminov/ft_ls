/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <ahonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:52:52 by ahonchar          #+#    #+#             */
/*   Updated: 2018/04/17 21:29:18 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(src);
	while (i < len)
	{
		if (i < j)
			dst[i] = src[i];
		else
			dst[i] = '\0';
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
