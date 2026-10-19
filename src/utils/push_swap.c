
#include "../../includes/push_swap.h"
void ft_start(char mode, t_node **a, t_node **b)
{
    int disorder;

    disorder = 0;
    if (mode == 'a')
        disorder = compute_disorder(*a, stack_size(*a));
    else if (mode == 's')
        disorder = 20;
    else if (mode == 'm')
        disorder = 40;
    else if (mode == 'c')
        disorder = 60;
    ft_call_algo(disorder, a, b);
}

void ft_call_algo(int disorder, t_node **a, t_node **b)
{
    if (disorder <= 20)
        simple_algorithme(a, b);
    else if (disorder > 20 && disorder <= 50)
        medium_algorithme(a, b);
    else if (disorder > 50)
        complex_algorithme(a, b);
}