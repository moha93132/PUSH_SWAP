/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 16:34:06 by mohasnao          #+#    #+#             */
/*   Updated: 2026/10/15 15:13:25 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	simple_algorithme(int *a, int n)
{
	int	i;
	int	j;
	int	tmp;
	int	swap;

	i = 0;
	swap = 1;
	while (i < n - 1 && swap == 1)
	{
		swap = 0;
		j = 0;
		while (j + 1 < n)
		{
			if (a[j] > a[j + 1])
			{
				tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
				swap = 1;
			}
			j++;
		}
		i++;
	}
}



void	medium_algorithme(t_node **a, t_node **b)
{
	int	n;
	int	nbr_bits;
	int	bit;

	n = stack_size(*a);
	init_radix(*a);
	init_rank(*a,n);
	nbr_bits = get_nbr_bits(n);
	bit = 0;
	while (bit < nbr_bits)
	{
		radix_pass(a, b, n, bit);
		bit++;
	}
}
