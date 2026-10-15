/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_dsorder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohasnao <mohasnao@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 16:50:22 by mohasnao          #+#    #+#             */
/*   Updated: 2026/10/15 12:26:12 by mohasnao         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	compute_disorder(int *a, int n)
{
	int	mistakes;
	int	total_pairs;
	int	i;

	mistakes = 0;
	total_pairs = n - 1;
	i = 0;
	if (n < 2)
		return (0);
	while (i < n - 1)
	{
		if (a[i] > a[i + 1])
			mistakes++;
		i++;
	}
	return (mistakes * 100 / total_pairs);
}

int	ft_error(void)
{
	ft_putstr_fd("Error\n", 2);
	return (1);
}

void	ft_free_stack(t_node **stack)
{
	t_node	*current;
	t_node	*next;

	if (!stack)
		return ;
	current = *stack;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*stack = NULL;
}
