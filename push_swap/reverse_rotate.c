/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 11:24:32 by yannis            #+#    #+#             */
/*   Updated: 2024/12/15 00:14:14 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "push_swap.h"

void reverse_rotate(t_stack *stack)
{
    int temp;
    int i;

    if (stack->top <= 0)
        return; // Rien à faire si la pile est vide ou a un seul élément

    temp = stack->arr[0];
    for (i = 0; i < stack->top; i++)
    {
        stack->arr[i] = stack->arr[i + 1];
    }
    stack->arr[stack->top] = temp;
}

void reverse_rotate_a(t_stack *stack_a)
{
    reverse_rotate(stack_a);
    write(1, "rra\n", 4);
}

void reverse_rotate_b(t_stack *stack_b)
{
    reverse_rotate(stack_b);
    write(1, "rrb\n", 4);
}

void reverse_rotate_all(t_stack *stack_a, t_stack *stack_b)
{
    reverse_rotate(stack_a);
    reverse_rotate(stack_b);
    write(1, "rrr\n", 4);
}
