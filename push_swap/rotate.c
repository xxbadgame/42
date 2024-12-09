/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 10:35:16 by yannis            #+#    #+#             */
/*   Updated: 2024/12/09 12:24:59 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "push_swap.h"

void rotate_a(t_stack *stack_a)
{
    int temp;
    int i;

    temp = stack_a->arr[stack_a->top];
    i = stack_a->top;
    while (i > 0)
    {
        stack_a->arr[i] =  stack_a->arr[i - 1];
        i--;
    }
    stack_a->arr[i] = temp;
    
    write(1, "ra\n", 3);
}

void rotate_b(t_stack *stack_b)
{
    int temp;
    int i;

    temp = stack_b->arr[stack_b->top];
    i = stack_b->top;
    while (i > 0)
    {
        stack_b->arr[i] =  stack_b->arr[i - 1];
        i--;
    }
    stack_b->arr[i] = temp;
    
    write(1, "rb\n", 3);
}

void rotate_all(t_stack *stack_a, t_stack *stack_b)
{
    int temp;
    int i;

    temp = stack_a->arr[stack_a->top];
    i = stack_a->top;
    while (i > 0)
    {
        stack_a->arr[i] =  stack_a->arr[i - 1];
        i--;
    }
    stack_a->arr[i] = temp;

    temp = stack_b->arr[stack_b->top];
    i = stack_b->top;
    while (i > 0)
    {
        stack_b->arr[i] =  stack_b->arr[i - 1];
        i--;
    }
    stack_b->arr[i] = temp;

    write(1, "rr\n", 4);
}