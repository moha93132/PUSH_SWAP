#include "../../includes/push_swap.h"

static void ft_put_disorder(double disorder)
{
	int value;

	value = (int)(disorder * 10000 + 0.5);
	ft_putstr_fd("[bench] disorder: ", 2);
	ft_putnbr_fd(value / 100, 2);
	ft_putstr_fd(".", 2);
	if (value % 100 < 10)
		ft_putstr_fd("0", 2);
	ft_putnbr_fd(value % 100, 2);
	ft_putstr_fd("%\n", 2);
}

int *ft_print_op(char *op, int id)
{
	static int ops[11];

	if (op)
	{
		write(1, op, ft_strlen(op));
		ops[id]++;
	}
	return (ops);
}

void ft_print_bench(double disorder, char *strategy)
{
	char *names;
	int *ops;
	int total;
	int i;

	names = "sa  sb  ss  pa  pb  ra  rb  rr  rra rrb rrr ";
	ops = ft_print_op(NULL, 0);
	ft_put_disorder(disorder);
	ft_putstr_fd("[bench] strategy: ", 2);
	ft_putendl_fd(strategy, 2);
	total = 0;
	i = -1;
	while (++i < 11)
		total += ops[i];
	ft_putstr_fd("[bench] total_ops: ", 2);
	ft_putnbr_fd(total, 2);
	i = -1;
	while (++i < 11)
	{
		ft_putstr_fd("\n[bench] ", 2);
		write(2, names + i * 4, 4);
		ft_putnbr_fd(ops[i], 2);
	}
	ft_putstr_fd("\n", 2);
}
