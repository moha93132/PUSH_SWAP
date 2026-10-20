/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_rotate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mluvisot <mluvisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 21:58:47 by mohasnao          #+#    #+#             */
/*   Updated: 2026/10/19 14:23:56 by mluvisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static int ft_rotate(t_node **stack)
{
	t_node *first;
	t_node *last;

	if (!stack || !*stack || !(*stack)->next)
		return (0);
	first = *stack;
	*stack = first->next;
	first->next = NULL;
	last = *stack;
	while (last->next)
		last = last->next;
	last->next = first;
	return (1);
}

void ra(t_node **a)
{
	if (ft_rotate(a))
		ft_print_op("ra\n", 5);
}

void rb(t_node **b)
{
	if (ft_rotate(b))
		ft_print_op("rb\n", 6);
}

void rr(t_node **a, t_node **b)
{
	int rotate_a;
	int rotate_b;

	rotate_a = ft_rotate(a);
	rotate_b = ft_rotate(b);
	if (rotate_a || rotate_b)
		 ft_print_op("rr\n", 7);
}
