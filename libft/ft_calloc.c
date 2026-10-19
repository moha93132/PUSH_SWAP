/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohasnao <mohasnao@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 12:16:47 by mohasnao          #+#    #+#             */
/*   Updated: 2026/10/10 02:47:03 by mohasnao         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*list;
	char	*tmp;
	size_t	i;

	if (nmemb * size > 2147483647)
		return (NULL);
	if (nmemb != 0 && size > ((size_t) - 1) / nmemb)
		return (NULL);
	list = malloc(nmemb * size);
	if (!list)
		return (NULL);
	tmp = (char *) list;
	i = 0;
	while (i < nmemb * size)
	{
		tmp[i] = '\0';
		i++;
	}
	return (list);
}
