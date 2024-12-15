/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 10:35:16 by yannis            #+#    #+#             */
/*   Updated: 2024/12/15 00:17:05 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "push_swap.h"

void rotate(t_stack *stack)
{
    int temp;
    int i;

    if (stack->top <= 0)
        return; // Rien à faire si la pile est vide ou a un seul élément

    temp = stack->arr[stack->top];
    for (i = stack->top; i > 0; i--)
    {
        stack->arr[i] = stack->arr[i - 1];
    }
    stack->arr[0] = temp;
}

void rotate_a(t_stack *stack_a)
{
    rotate(stack_a);
    write(1, "ra\n", 3);
}

void rotate_b(t_stack *stack_b)
{
    rotate(stack_b);
    write(1, "rb\n", 3);
}

void rotate_all(t_stack *stack_a, t_stack *stack_b)
{
    rotate(stack_a);
    rotate(stack_b);
    write(1, "rr\n", 3);
}
