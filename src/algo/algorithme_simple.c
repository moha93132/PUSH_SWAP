/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithme_simple.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mluvisot <mluvisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:05:23 by mohasnao          #+#    #+#             */
/*   Updated: 2026/10/19 14:24:27 by mluvisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int stack_size(t_node *a)
{
	int size;

	size = 0;
	while (a)
	{
		size++;
		a = a->next;
	}
	return (size);
}
/*
static void	add_index(t_node *a)
{
	t_node	*current;
	t_node	*compare;
	int		index;

	current = a;
	while (current)
	{
		index = 0;
		compare = a;
		while (compare)
		{
			if (compare->value < current->value)
				index++;
			compare = compare->next;
		}
		current->index = index;
		current = current->next;
	}
}
*/

int find_index_position(t_node *a, int index)
{
	int position;

	position = 0;
	while (a)
	{
		if (a->index == index)
			return (position);
		a = a->next;
		position++;
	}
	return (-1);
}

void simple_algorithme(t_node **a, t_node **b)
{
	int index;
	int position;
	int size_a;

	index = 0;
	while (*a)
	{
		position = find_index_position(*a, index);
		size_a = stack_size(*a);
		if (position <= size_a / 2)
			while (position-- > 0)
				ra(a);
		else
			while (position++ < size_a)
				rra(a);
		pb(a, b);
		index++;
	}
	while (*b)
		pa(a, b);
}
