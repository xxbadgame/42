/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 15:17:17 by yannis            #+#    #+#             */
/*   Updated: 2024/12/20 21:30:51 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../push_swap.h"

void push_median_numbers(t_stack *stack_a, t_stack *stack_b)
{
    int median;
    int i;
    int new_min;

    i = 0;
    median = stack_a->arr[find_min_ind(stack_a)];
    while (i < (stack_a->top / 2 - 1))
    {
        new_min = stack_a->arr[closest_bigger_target(median, stack_a)];
        median = new_min;
        i++;
    }
    
    while (stack_a->top > 2)
    {
        push_b(stack_a,stack_b);
        if (stack_b->arr[stack_b->top] > median)
            rotate_b(stack_b);
    }
}

void turk_sort(t_stack *stack_a, t_stack *stack_b)
{
    int ind_target;
    int ind_element;
    int target;
    int element;
    
    while (stack_b->top >= 0)
    {
        ind_element = cost_push(stack_a, stack_b);
        ind_target = closest_bigger_target(stack_b->arr[ind_element], stack_a);
        target = stack_a->arr[ind_target];
        element = stack_b->arr[ind_element];

        complete_rotation_one(stack_a, stack_b, ind_element, ind_target);
        complete_rotation_two(stack_a, ind_target, target);
        complete_rotation_three(stack_b,  ind_element, element);
        
        push_a(stack_a, stack_b);
    }
    complete_rotation_four(stack_a);
}

void push_swap(t_stack *stack_a, t_stack *stack_b)
{
    push_median_numbers(stack_a, stack_b);
    sort_three(stack_a);
    turk_sort(stack_a, stack_b);
}

int main(int argc, char **argv)
{
    t_stack stack_a;
    t_stack stack_b;
    stack_a.top = -1;
    stack_b.top = -1;
   
    argc = argc - 1;
    while (argc >= 1)
    {
        stack_a.arr[++stack_a.top] = atoi(argv[argc]);
        argc--;
    }

    push_swap(&stack_a, &stack_b);
}