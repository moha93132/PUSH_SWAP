/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mluvisot <mluvisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 20:48:45 by mohasnao          #+#    #+#             */
/*   Updated: 2026/10/21 14:59:56 by mluvisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static	char	*ft_name(char mode, char algo)
{
	if (mode == 'a' && algo == 's')
		return ("Adaptive -> Simple O(n^2)");
	if (mode == 'a' && algo == 'm')
		return ("Adaptive -> Medium O(n*sqrt(n))");
	if (mode == 'a')
		return ("Adaptive -> Complex O(n log n)");
	if (algo == 's')
		return ("Simple O(n^2)");
	if (algo == 'm')
		return ("Medium O(n*sqrt(n))");
	return ("Complex O(n log n)");
}

void	init_index(t_node *node)
{
	while (node)
	{
		node->index = -1;
		node = node->next;
	}
}

void	init_rank(t_node *a, int size)
{
	t_node	*node;
	t_node	*min;
	int		rank;

	rank = 0;
	while (rank < size)
	{
		min = NULL;
		node = a;
		while (node)
		{
			if (node->index == -1 && (!min || node->value < min->value))
				min = node;
			node = node->next;
		}
		min->index = rank;
		rank++;
	}
}

static void	sort_small(t_node **a, t_node **b, int size)
{
	if (size == 2)
		sa(a);
	else if (size == 3)
		sort_three(a);
	else
		sort_five(a, b);
}

void	ft_start(char mode, int bench, t_node **a, t_node **b)
{
	double	disorder;
	char	algo;
	int		size;

	disorder = compute_disorder(*a);
	algo = conditions(mode, disorder);
	size = stack_size(*a);
	init_index(*a);
	init_rank(*a, size);
	if (disorder > 0 && mode == 'a' && size <= 5)
		sort_small(a, b, size);
	else if (disorder > 0 && algo == 's')
		simple_algorithme(a, b);
	else if (disorder > 0 && algo == 'm')
		medium_algorithme(a, b);
	else if (disorder > 0)
		complex_algorithme(a, b);
	if (bench)
		ft_print_bench(disorder, ft_name(mode, algo));
}
