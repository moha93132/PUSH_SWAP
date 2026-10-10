/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_push.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohasnao <mohasnao@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 21:51:42 by mohasnao          #+#    #+#             */
/*   Updated: 2026/10/10 21:57:11 by mohasnao         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	ft_push(t_node **src, t_node **dst)
{
	t_node	*node;

	if (!src || !*src)
		return (0);
	node = *src;
	*src = node->next;
	node->next = *dst;
	*dst = node;
	return (1);
}

void	pa(t_node **a, t_node **b)
{
	if (ft_push(b, a))
		ft_putstr("pa\n", 1);
}

void	pb(t_node **a, t_node **b)
{
	if (ft_push(a, b))
		ft_putstr("pb\n", 1);
}
