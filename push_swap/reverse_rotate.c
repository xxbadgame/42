/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 11:24:32 by yannis            #+#    #+#             */
/*   Updated: 2024/12/07 11:33:12 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "push_swap.h"

void reverse_rotate_a(t_stack *stack_a)
{
    int temp;
    int i;

    temp = stack_a->arr[0];
    i = 0;
    while (i < stack_a->top)
    {
        stack_a->arr[i] =  stack_a->arr[i + 1];
        i++;
    }
    stack_a->arr[i] = temp;
    
    write(1, "rra\n", 4);
}

void reverse_rotate_b(t_stack *stack_b)
{
    int temp;
    int i;

    temp = stack_b->arr[0];
    i = 0;
    while (i < stack_b->top)
    {
        stack_b->arr[i] =  stack_b->arr[i + 1];
        i++;
    }
    stack_b->arr[i] = temp;
    
    write(1, "rrb\n", 4);
}

void reverse_rotate_all(t_stack *stack_a, t_stack *stack_b)
{
    reverse_rotate_a(stack_a);
    reverse_rotate_b(stack_b);
    write(1, "rrr\n", 4);
}