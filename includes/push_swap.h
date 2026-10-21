/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mluvisot <mluvisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 16:35:10 by mohasnao          #+#    #+#             */
/*   Updated: 2026/10/21 15:24:13 by mluvisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "../libft/libft.h"

/* Structure */
typedef struct s_node
{
	int				value;
	int				index;
	struct s_node	*next;
}					t_node;

int		ft_get_mod(int argc, char **argv, char *mode, int *bench);
long	ft_atol(char *s);
int		ft_is_number(char *s);
int		ft_has_dup(t_node *a, int value);
int		ft_init(t_node **a, int argc, char **argv, int start);
char	conditions(char mode, double disorder);
int		valid_indices(t_node *a, int size);
void	ft_start(char mode, int bench, t_node **a, t_node **b);
void	ft_print_bench(double disorder, char *strategy);
double	compute_disorder(t_node *a);
int		*ft_print_op(char *op, int id);
int		ft_error(void);
void	ft_free_stack(t_node **stack);
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
int		stack_size(t_node *a);
int		find_index_position(t_node *a, int index);
void	simple_algorithme(t_node **a, t_node **b);
void	medium_algorithme(t_node **a, t_node **b);
void	init_index(t_node *node);
void	init_rank(t_node *a, int size);
void	radix_pass(t_node **a, t_node **b, int n, int bit);
void	complex_algorithme(t_node **a, t_node **b);
void	sort_three(t_node **a);
void	sort_five(t_node **a, t_node **b);

#endif