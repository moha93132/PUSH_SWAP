/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_reverse_rotate.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mluvisot <mluvisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 22:05:37 by mohasnao          #+#    #+#             */
/*   Updated: 2026/10/19 14:26:46 by mluvisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static int ft_reverse_rotate(t_node **stack)
{
	t_node *last;
	t_node *prev;

	if (!stack || !*stack || !(*stack)->next)
		return (0);
	last = *stack;
	while (last->next)
	{
		prev = last;
		last = last->next;
	}
	prev->next = NULL;
	last->next = *stack;
	*stack = last;
	return (1);
}

void rra(t_node **a)
{
	if (ft_reverse_rotate(a))
		write(1, "rra\n", 4);
}

void rrb(t_node **b)
{
	if (ft_reverse_rotate(b))
		write(1, "rrb\n", 4);
}

void rrr(t_node **a, t_node **b)
{
	int rotate_a;
	int rotate_b;

	rotate_a = ft_reverse_rotate(a);
	rotate_b = ft_reverse_rotate(b);
	if (rotate_a || rotate_b)
		write(1, "rrr\n", 4);
}
