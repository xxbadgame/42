/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:58:23 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/12/20 21:21:16 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../push_swap.h"

void display_stacks(t_stack *stack_a, t_stack *stack_b)
{
	int i;
    int j;
    
	i = stack_a->top;
    j = stack_b->top;
	printf("-----------------------------------------------------------\n");
	while (i >= 0 || j >= 0)
    {
        if (i >= 0)
            printf("%d\t", stack_a->arr[i--]);
        else
            printf("\t");
        if (j >= 0)
            printf("%d\n", stack_b->arr[j--]);
        else
            printf("\n");
    }
	printf("_       _\n");
	printf("a       b\n");
}

int ft_abs(int value)
{
    return (value > 0) * value + (value < 0) * -value; 
}

int find_max_ind(t_stack *stack)
{
    int i;
    int ind;
    int max;

    i = 0;
    ind = 0;
    max = stack->arr[0];
    while (i <= stack->top)
    {
        if (stack->arr[i] > max)
        {
            max = stack->arr[i];
            ind = i;
        }    
        i++;
    }
    return (ind);
}

int find_min_ind(t_stack *stack)
{
    int i;
    int ind;
    int min;

    i = 0;
    ind = 0;
    min = stack->arr[0];
    while (i <= stack->top)
    {
        if (stack->arr[i] <= min)
        {
            min = stack->arr[i];
            ind = i;
        }    
        i++;
    }
    return (ind);
}

int closest_bigger_target(int value, t_stack *stack_a)
{
    int i;
    int ind_target;
    int min_diff;

    i = stack_a->top;
    ind_target = i;
    min_diff = INT_MAX;
    while (i >= 0)
    {
        if(stack_a->arr[i] > value && ft_abs(stack_a->arr[i] - value) < min_diff)
        {
            min_diff = ft_abs(stack_a->arr[i] - value);
            ind_target = i;
        }
        i--;
    }
    if (min_diff == INT_MAX)
        ind_target = find_min_ind(stack_a);
    return (ind_target);
}