/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_dsorder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohasnao <mohasnao@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 16:50:22 by mohasnao          #+#    #+#             */
/*   Updated: 2026/10/10 20:28:16 by mohasnao         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	compute_disorder(int *a)
{
	int	mistakes;
	int	total_pairs;
	int	i;
	int	j;

	i = 0;
	mistakes = 0;
	total_pairs = 0;
	while (i < size(a) - 1)
	{
		j = i + 1;
		total_pairs++;
		if (a[i] > a[j])
			mistakes++;
		i++;
	}
	return (mistakes * 100 / total_pairs);
}

int	ft_error(void)
{
	return (1);
}
