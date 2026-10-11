/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohasnao <mohasnao@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 16:35:10 by mohasnao          #+#    #+#             */
/*   Updated: 2026/10/11 17:42:47 by mohasnao         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <limits.h>

/* Structure */
typedef struct s_node
{
	int				value;
	int				index;
	struct s_node	*next;
}	t_node;

/* Parsing */
long	ft_atol(char *s);
int		ft_is_number(char *s);
int		ft_has_dup(t_node *a, int value);
int		ft_init(t_node **a, int argc, char **argv);

/* Error */
int		ft_error(void);
void	ft_free_stack(t_node **stack);

/* Operations */
void	sa(t_node **a);
void	sb(t_node **b);
void	ss(t_node **a, t_node **b);
void	pa(t_node **a, t_node **b);
void	pb(t_node **a, t_node **b);
void	ra(t_node **a);
void	rb(t_node **b);
void	rr(t_node **a, t_node **b);
void	rra(t_node **a);
void	rrb(t_node **b);
void	rrr(t_node **a, t_node **b);

/* Algorithmes de tri */
void	simple_algorithme(int *a, int n);
int		medium_algorithme(int *a, int n);
int		compute_disorder(int *a, int n);
#endif