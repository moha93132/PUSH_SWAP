/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithme_plist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohasnao <mohasnao@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 15:04:43 by mohasnao          #+#    #+#             */
/*   Updated: 2026/10/20 15:24:07 by mohasnao         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	sort_three(t_node **a)
{
	int	first;
	int	second;
	int	third;

	first = (*a)->value;
	second = (*a)->next->value;
	third = (*a)->next->next->value;
	if (first < second && second < third)
		return ;
	if (first > second && second < third && first < third)
		sa(a);
	else if (first > second && second > third)
	{
		sa(a);
		rra(a);
	}
	else if (first > second && first > third)
		ra(a);
	else if (first < second && second > third && first < third)
	{
		sa(a);
		ra(a);
	}
	else
		rra(a);
}

static int	find_min_position(t_node *a)
{
	int		min;
	int		position;
	int		min_position;

	min = a->value;
	position = 0;
	min_position = 0;
	while (a)
	{
		if (a->value < min)
		{
			min = a->value;
			min_position = position;
		}
		a = a->next;
		position++;
	}
	return (min_position);
}

void	sort_five(t_node **a, t_node **b)
{
	int	position;
	int	size;

	while (stack_size(*a) > 3)
	{
		position = find_min_position(*a);
		size = stack_size(*a);
		if (position <= size / 2)
		{
			while (position-- > 0)
				ra(a);
		}
		else
		{
			while (position++ < size)
				rra(a);
		}
		pb(a, b);
	}
	sort_three(a);
	while (*b)
		pa(a, b);
}
