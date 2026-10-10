/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohasnao <mohasnao@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 12:19:03 by mohasnao          #+#    #+#             */
/*   Updated: 2026/10/06 15:04:52 by mohasnao         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char	*dest, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < dstsize && dest[i])
		i++;
	if (i == dstsize)
	{
		while (src[j])
			j++;
		return (i + j);
	}
	while (i + j < dstsize - 1 && src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	if (i + j < dstsize)
		dest[i + j] = '\0';
	while (src[j])
		j++;
	return (i + j);
}
