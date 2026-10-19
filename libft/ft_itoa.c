/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohasnao <mohasnao@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 12:17:19 by mohasnao          #+#    #+#             */
/*   Updated: 2026/10/10 03:15:10 by mohasnao         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*min(int n)
{
	char	*res;

	if (n == 0)
	{
		res = malloc(2);
		if (!res)
			return (NULL);
		res[0] = '0';
		res[1] = '\0';
		return (res);
	}
	res = malloc(12);
	if (!res)
		return (NULL);
	ft_strlcpy(res, "-2147483648", 12);
	return (res);
}

static int	len_num(int x)
{
	int	len;

	len = 0;
	if (x <= 0)
		len++;
	while (x)
	{
		x = x / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		len;
	int		i;

	if (n == -2147483648 || n == 0)
		return (min(n));
	len = len_num(n);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	res[len] = '\0';
	i = len;
	if (n < 0)
	{
		res[0] = '-';
		n = -n;
	}
	while (n)
	{
		res[--i] = (n % 10) + '0';
		n /= 10;
	}
	return (res);
}
