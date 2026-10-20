#include "../../includes/push_swap.h"

static char	*ft_name(char mode, char algo)
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

static int	is_sorted(t_node *a)
{
	while (a && a->next)
	{
		if (a->value > a->next->value)
			return (0);
		a = a->next;
	}
	return (1);
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

void	ft_start(char mode, int bench, t_node **a, t_node **b)
{
	double	disorder;
	char	algo;

	disorder = compute_disorder(*a);
	init_index(*a);
	init_rank(*a, stack_size(*a));
	algo = mode;
	if (mode == 'a' && disorder < 0.2)
		algo = 's';
	else if (mode == 'a' && disorder < 0.5)
		algo = 'm';
	else if (mode == 'a')
		algo = 'c';
	if (!is_sorted(*a))
	{
		if (algo == 's')
			simple_algorithme(a, b);
		else if (algo == 'm')
			medium_algorithme(a, b);
		else
			complex_algorithme(a, b);
	}
	if (bench)
		ft_print_bench(disorder, ft_name(mode, algo));
}