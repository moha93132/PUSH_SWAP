/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_push.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mluvisot <mluvisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 21:51:42 by mohasnao          #+#    #+#             */
/*   Updated: 2026/10/19 14:26:34 by mluvisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static int ft_push(t_node **src, t_node **dst)
{
	t_node *node;

	if (!src || !*src)
		return (0);
	node = *src;
	*src = node->next;
	node->next = *dst;
	*dst = node;
	return (1);
}

void pa(t_node **a, t_node **b)
{
	if (ft_push(b, a))
		write(1, "pa\n", 3);
}

void pb(t_node **a, t_node **b)
{
	if (ft_push(a, b))
		write(1, "pb\n", 3);
}
