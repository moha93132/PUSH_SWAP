#include "../../includes/push_swap.h"

long ft_atol(char *s)
{
	long res;
	int sign;
	int i;

	res = 0;
	sign = 1;
	i = 0;
	if (ft_strlen(s) > 11)
		return (2147483648L);
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

int ft_is_number(char *s)
{
	int i;

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

int ft_get_mod(int argc, char **argv, char *mode, int *bench)
{
	int i;

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

int ft_error(void)
{
	ft_putstr_fd("Error\n", 2);
	return (1);
}

void ft_free_stack(t_node **stack)
{
	t_node *current;
	t_node *next;

	if (!stack)
		return;
	current = *stack;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*stack = NULL;
}
