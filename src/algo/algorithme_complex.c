/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithme_complex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mluvisot <mluvisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 15:12:10 by marco             #+#    #+#             */
/*   Updated: 2026/10/19 14:24:17 by mluvisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static int	get_nbr_bits(int n)
{
	int	bits;

	bits = 0;
	while (((n - 1) >> bits) != 0)
		bits++;
	return (bits);
}

void	init_radix(t_node *node)
{
	while (node)
	{
		node->index = -1;
		node = node->next;
	}
}

void	init_rank(t_node *a, int size)
{
	t_node	*node;
	t_node	*min;
	int		rank;

	rank = 0;
	while (rank < size)
	{
		min = NULL;
		node = a;
		while (node)
		{
			if (node->index == -1 && (!min || node->value < min->value))
				min = node;
			node = node->next;
		}
		min->index = rank;
		rank++;
	}
}
void	radix_pass(t_node **a, t_node **b, int n, int bit)
{
	int	i;

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

void	complex_algorithme(t_node **a, t_node **b)
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
