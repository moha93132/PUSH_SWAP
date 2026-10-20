/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mluvisot <mluvisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 15:00:05 by mluvisot          #+#    #+#             */
/*   Updated: 2026/10/20 20:51:42 by mohasnao         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int	ft_has_dup(t_node *a, int value)
{
	while (a)
	{
		if (a->value == value)
			return (1);
		a = a->next;
	}
	return (0);
}

static int	ft_add_back(t_node **a, int value)
{
	t_node	*new;
	t_node	*last;

	new = malloc(sizeof(t_node));
	if (!new)
		return (0);
	new->value = value;
	new->index = -1;
	new->next = NULL;
	if (!*a)
	{
		*a = new;
		return (1);
	}
	last = *a;
	while (last->next)
		last = last->next;
	last->next = new;
	return (1);
}

int	ft_init(t_node **a, int argc, char **argv, int start)
{
	int		i;
	long	nbr;

	i = start;
	while (i < argc)
	{
		if (!ft_is_number(argv[i]))
			return (ft_free_stack(a), ft_error());
		nbr = ft_atol(argv[i]);
		if (nbr > INT_MAX || nbr < INT_MIN)
			return (ft_free_stack(a), ft_error());
		if (ft_has_dup(*a, (int)nbr))
			return (ft_free_stack(a), ft_error());
		if (!ft_add_back(a, (int)nbr))
			return (ft_free_stack(a), ft_error());
		i++;
	}
	return (0);
}

char	conditions(char mode, double disorder)
{
	if (mode != 'a')
		return (mode);
	if (disorder < 0.2)
		return ('s');
	else if (disorder < 0.5)
		return ('m');
	return ('c');
}

int	valid_indices(t_node *a, int size)
{
	t_node	*current;
	t_node	*compare;

	current = a;
	while (current)
	{
		if (current->index < 0 || current->index >= size)
			return (0);
		compare = current->next;
		while (compare)
		{
			if (current->index == compare->index)
				return (0);
			compare = compare->next;
		}
		current = current->next;
	}
	return (1);
}
