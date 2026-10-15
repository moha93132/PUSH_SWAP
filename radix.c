/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 15:12:10 by marco             #+#    #+#             */
/*   Updated: 2026/10/15 15:13:21 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_nbr_bits(int n)
{
	int	bits;

	bits = 0;
	while (((n - 1) >> bits) != 0)
		bits++;
	return (bits);
}

int	stack_size(t_node *node)
{
	int	size;

	size = 0;
	while (node)
	{
		size++;
		node = node->next;
	}
	return (size);
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
