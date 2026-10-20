/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mluvisot <mluvisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 13:25:36 by mluvisot          #+#    #+#             */
/*   Updated: 2026/10/20 10:24:40 by mluvisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/push_swap.h"

int main(int argc, char **argv)
{
	t_node *a;
	t_node *b;
	char mode;
	int bench;
	int i;

	if (argc < 2)
		return (0);
	mode = 0;
	bench = 0;
	i = ft_get_mod(argc, argv, &mode, &bench);
	if (i == -1)
		return (ft_error());
	if (i == argc)
		return (0);
	a = NULL;
	b = NULL;
	if (ft_init(&a, argc, argv, i))
		return (1);
	ft_start(mode, bench, &a, &b);
	ft_free_stack(&a);
	ft_free_stack(&b);
	return (0);
}
