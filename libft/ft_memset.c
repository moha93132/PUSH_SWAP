/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohasnao <mohasnao@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 12:18:22 by mohasnao          #+#    #+#             */
/*   Updated: 2026/10/06 16:03:46 by mohasnao         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t nb)
{
	size_t			i;
	unsigned char	*tmp;

	i = 0;
	tmp = (unsigned char *) str;
	while (i < nb)
	{
		tmp[i] = c;
		i++;
	}
	return (str);
}
