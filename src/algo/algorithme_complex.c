/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithme_complex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mluvisot <mluvisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 15:12:10 by marco             #+#    #+#             */
/*   Updated: 2026/10/20 10:24:11 by mluvisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static int get_nbr_bits(int n)
{
	int bits;

	bits = 0;
	while (((n - 1) >> bits) != 0)
		bits++;
	return (bits);
}

void radix_pass(t_node **a, t_node **b, int n, int bit)
{
	int i;

	i = 0;
	while (i < n)
	{
		if ((((*a)->index >> bit) & 1) == 0)
			pb(a, b);
		else
			ra(a);
		i++;
	}
	while (*b)
		pa(a, b);
}

void complex_algorithme(t_node **a, t_node **b)
{
	int n;
	int nbr_bits;
	int bit;

	n = stack_size(*a);
	init_radix(*a);
	init_rank(*a, n);
	nbr_bits = get_nbr_bits(n);
	bit = 0;
	while (bit < nbr_bits)
	{
		radix_pass(a, b, n, bit);
		bit++;
	}
}
