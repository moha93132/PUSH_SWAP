/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohasnao <mohasnao@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 12:11:25 by mohasnao          #+#    #+#             */
/*   Updated: 2026/10/06 12:16:16 by mohasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	signe;
	int	nb;

	i = 0;
	nb = 0;
	signe = 1;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		signe = -signe;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] > '0' && str[i] < '9')
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	return (nb * signe);
}
