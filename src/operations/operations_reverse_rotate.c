/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_reverse_rotate.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mluvisot <mluvisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 22:05:37 by mohasnao          #+#    #+#             */
/*   Updated: 2026/10/20 20:49:15 by mohasnao         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static int	ft_reverse_rotate(t_node **stack)
{
	t_node	*last;
	t_node	*prev;

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

void	rra(t_node **a)
{
	if (ft_reverse_rotate(a))
		ft_print_op("rra\n", 8);
}

void	rrb(t_node **b)
{
	if (ft_reverse_rotate(b))
		ft_print_op("rrb\n", 9);
}

void	rrr(t_node **a, t_node **b)
{
	int	rotate_a;
	int	rotate_b;

	rotate_a = ft_reverse_rotate(a);
	rotate_b = ft_reverse_rotate(b);
	if (rotate_a || rotate_b)
		ft_print_op("rrr\n", 10);
}
