/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohasnao <mohasnao@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 12:19:09 by mohasnao          #+#    #+#             */
/*   Updated: 2026/10/06 15:04:56 by mohasnao         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t ldst)
{
	size_t	i;

	i = 0;
	if (ldst == 0)
	{
		while (src[i])
			i++;
		return (i);
	}
	while (src[i] && i < ldst - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	while (src[i])
		i++;
	return (i);
}
