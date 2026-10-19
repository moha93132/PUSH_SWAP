/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_dsorder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mluvisot <mluvisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 16:50:22 by mohasnao          #+#    #+#             */
/*   Updated: 2026/10/19 14:24:09 by mluvisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int compute_disorder(t_node *a, int n)
{
	t_node *cmp;
	long mistakes;
	long total_pairs;

	if (n < 2)
		return (0);
	mistakes = 0;
	total_pairs = 0;
	cmp = a->next;
	while (cmp)
	{
		if (a->value > cmp->value)
			mistakes++;
		total_pairs++;
		a = a->next;
		cmp = a->next;
	}
	return ((int)(mistakes * 100 / total_pairs));
}

int ft_error(void)
{
	ft_putstr_fd("Error\n", 2);
	return (1);
}

void ft_free_stack(t_node **stack)
{
	t_node *current;
	t_node *next;

	if (!stack)
		return;
	current = *stack;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*stack = NULL;
}
