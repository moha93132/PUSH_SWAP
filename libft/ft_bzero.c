/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohasnao <mohasnao@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 12:16:37 by mohasnao          #+#    #+#             */
/*   Updated: 2026/10/06 14:57:25 by mohasnao         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t nb)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = (char *) str;
	while (i < nb)
	{
		tmp[i] = '\0';
		i++;
	}
}
