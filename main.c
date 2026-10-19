/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mluvisot <mluvisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 13:25:36 by mluvisot          #+#    #+#             */
/*   Updated: 2026/10/19 12:12:03 by mluvisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_get_mod(int argc, char **argv, char *mode, int *bench)
{
	int	i;

	i = 1;
	while (i < argc && ft_strncmp(argv[i], "--", 2) == 0)
	{
		if (ft_strncmp(argv[i], "--bench", 8) == 0 && !*bench)
			*bench = 1;
		else if (ft_strncmp(argv[i], "--simple", 9) == 0 && !*mode)
			*mode = 's';
		else if (ft_strncmp(argv[i], "--medium", 9) == 0 && !*mode)
			*mode = 'm';
		else if (ft_strncmp(argv[i], "--complex", 10) == 0 && !*mode)
			*mode = 'c';
		else if (ft_strncmp(argv[i], "--adaptive", 11) == 0 && !*mode)
			*mode = 'a';
		else
			return (-1);
		i++;
	}
	if (!*mode)
		*mode = 'a';
	return (i);
}

int	main(int argc, char **argv)
{
	t_node	*a;
	t_node	*b;
	char	mode;
	int		bench;
	int		i;

	if (argc < 2)
		return (0);
	mode = 0;
	bench = 0;
	i = ft_get_mod(argc, argv, &mode, &bench);
	if (i == -1)
	{
		ft_error("erreur le mode selctionne n'existe pas");
		return (1);
	}
	if (i == argc)
		return (0);
	a = NULL;
	b = NULL;
	if (ft_init(&a, argc, argv, i))
		return (1);
	ft_start(mode ,a, b)
	return (0);
}
