/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:53:07 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/12/06 17:32:50 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "push_swap.h"

void push_a(t_stack *stack_a, t_stack *stack_b)
{
	stack_a->top++;
	stack_a->arr[stack_a->top] = stack_b->arr[stack_b->top];
	stack_b->top--;
	write(1, "pa\n", 3);
}

void push_b(t_stack *stack_a, t_stack *stack_b)
{
	stack_b->top++;
	stack_b->arr[stack_b->top] = stack_a->arr[stack_a->top];
	stack_a->top--;
	write(1, "pa\n", 3);
}