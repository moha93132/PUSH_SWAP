/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mluvisot <mluvisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 15:00:05 by mluvisot          #+#    #+#             */
/*   Updated: 2026/10/10 20:29:20 by mohasnao         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

long	ft_atol(char *s)
{
	long	res;
	int		sign;
	int		i;

	res = 0;
	sign = 1;
	i = 0;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i])
	{
		res = res * 10 + (s[i] - '0');
		if (res * sign > INT_MAX || res * sign < INT_MIN)
			return (2147483648L);
		i++;
	}
	return (res * sign);
}

int	ft_is_number(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

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

void	ft_init(t_node **a, int argc, char **argv)
{
	int		i;
	long	nbr;

	i = 1;
	while (i < argc)
	{
		if (!ft_is_number(argv[i]))
			ft_error();
		nbr = ft_atol(argv[i]);
		if (nbr > INT_MAX || nbr < INT_MIN)
			ft_error();
		if (ft_has_dup(*a, (int)nbr))
			ft_error();
		if (!ft_add_back(a, (int)nbr))
			ft_error();
		i++;
	}
}
