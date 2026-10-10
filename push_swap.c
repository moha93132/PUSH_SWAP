/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohasnao <mohasnao@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 16:34:06 by mohasnao          #+#    #+#             */
/*   Updated: 2026/10/10 20:27:12 by mohasnao         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	simple_algorithme(int *a, int n)
{
	int	i;
	int	j;
	int	tmp;
	int	swap;

	i = 0;
	swap = 1;
	while (i < n - 1 && swap == 1)
	{
		swap = 0;
		j = 0;
		while (j + 1 < n)
		{
			if (a[j] > a[j + 1])
			{
				tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
				swap = 1;
			}
			j++;
		}
		i++;
	}
}

int	medium_algorithme(int *a, int n)
{
}
