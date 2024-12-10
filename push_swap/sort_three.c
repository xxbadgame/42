/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 23:05:39 by yannis            #+#    #+#             */
/*   Updated: 2024/12/10 23:24:08 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "push_swap.h"

void sort_three(t_stack *stack)
{
    int first;
    int second;
    int third;

    first = stack->arr[stack->top];
    second = stack->arr[stack->top - 1];
    third = stack->arr[stack->top - 2];

    if (first < second && second < third)
        return;
    if (first > second && second > third)
    {
        swap_a(stack);
        reverse_rotate_a(stack);
    }
    else if (first < third && second > third)
    {
        swap_a(stack);
        rotate_a(stack);
    }
    else if (first > third && second > first)
        rotate_a(stack);
    else if (second < third && first > third)
        reverse_rotate_a(stack);
    else if (first > second && second < third)
        swap_a(stack);
}