/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:53:07 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/01/14 17:04:19 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../checker.h"

void	push_a(t_stack *stack_a, t_stack *stack_b)
{
	stack_a->top++;
	stack_a->arr[stack_a->top] = stack_b->arr[stack_b->top];
	stack_b->top--;
}

void	push_b(t_stack *stack_a, t_stack *stack_b)
{
	stack_b->top++;
	stack_b->arr[stack_b->top] = stack_a->arr[stack_a->top];
	stack_a->top--;
}
