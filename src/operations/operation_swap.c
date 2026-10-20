/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_swap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mluvisot <mluvisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 21:28:37 by mohasnao          #+#    #+#             */
/*   Updated: 2026/10/19 14:24:02 by mluvisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static int ft_swap(t_node **stack)
{
	t_node *first;
	t_node *second;

	if (!stack || !*stack || !(*stack)->next)
		return (0);
	first = *stack;
	second = first->next;
	first->next = second->next;
	second->next = first;
	*stack = second;
	return (1);
}

void sa(t_node **a)
{
	if (ft_swap(a))
		ft_print_op("sa\n", 0);
}

void sb(t_node **b)
{
	if (ft_swap(b))
		ft_print_op("sb\n", 1);
}

void ss(t_node **a, t_node **b)
{
	int swap_a;
	int swap_b;

	swap_a = ft_swap(a);
	swap_b = ft_swap(b);
	if (swap_a || swap_b)
		 ft_print_op("ss\n", 2);
}
