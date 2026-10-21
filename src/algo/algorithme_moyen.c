/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithme_moyen.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mluvisot <mluvisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:27:49 by mohasnao          #+#    #+#             */
/*   Updated: 2026/10/21 15:01:11 by mluvisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static	int	get_chunk_size(int size)
{
	int	i;

	i = 1;
	while (i * i < size)
		i++;
	return (i + i / 2);
}

static	void	add_index(t_node *a)
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

static void	push_chunk(t_node **a, t_node **b, int max_index, int chunk_size)
{
	int	scan_size;
	int	i;

	scan_size = stack_size(*a);
	i = 0;
	while (*a && i < scan_size)
	{
		if ((*a)->index <= max_index)
		{
			pb(a, b);
			if ((*b)->index < max_index - chunk_size / 2)
				rb(b);
		}
		else
			ra(a);
		i++;
	}
}

static void	sort_back(t_node **a, t_node **b, int total_size)
{
	int	max_index;
	int	position;
	int	size_b;

	max_index = total_size - 1;
	while (*b)
	{
		size_b = stack_size(*b);
		position = find_index_position(*b, max_index);
		if (position <= size_b / 2)
		{
			while (position-- > 0)
				rb(b);
		}
		else
		{
			position = size_b - position;
			while (position-- > 0)
				rrb(b);
		}
		pa(a, b);
		max_index--;
	}
}

void	medium_algorithme(t_node **a, t_node **b)
{
	int	total_size;
	int	chunk_size;
	int	max_index;

	if (!a || !b || !*a || *b)
		return ;
	total_size = stack_size(*a);
	add_index(*a);
	if (total_size <= 1 || !valid_indices(*a, total_size))
		return ;
	chunk_size = get_chunk_size(total_size);
	max_index = chunk_size - 1;
	if (max_index >= total_size)
		max_index = total_size - 1;
	while (*a)
	{
		push_chunk(a, b, max_index, chunk_size);
		if (!*a || max_index >= total_size - 1)
			break ;
		if (max_index + chunk_size >= total_size)
			max_index = total_size - 1;
		else
			max_index += chunk_size;
	}
	sort_back(a, b, total_size);
}
