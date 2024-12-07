/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:53:14 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/12/07 10:33:55 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "push_swap.h"

void swap_a(t_stack *stack_a)
{
    int temp;

	temp = stack_a->arr[stack_a->top];
    stack_a->arr[stack_a->top] = stack_a->arr[stack_a->top - 1];
    stack_a->arr[stack_a->top - 1] = temp;
    write(1, "sa\n", 3);
}

void swap_b(t_stack *stack_b)
{
    int temp;

	temp = stack_b->arr[stack_b->top];
    stack_b->arr[stack_b->top] = stack_b->arr[stack_b->top - 1];
    stack_b->arr[stack_b->top - 1] = temp;
    write(1, "sb\n", 3);
}