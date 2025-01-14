/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 10:35:16 by yannis            #+#    #+#             */
/*   Updated: 2025/01/14 16:49:08 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	rotate(t_stack *stack)
{
	int	temp;
	int	i;

	if (stack->top <= 0)
		return ;
	i = stack->top;
	temp = stack->arr[stack->top];
	while (i > 0)
	{
		stack->arr[i] = stack->arr[i - 1];
		i--;
	}
	stack->arr[0] = temp;
}

void	rotate_a(t_stack *stack_a)
{
	rotate(stack_a);
	write(1, "ra\n", 3);
}

void	rotate_b(t_stack *stack_b)
{
	rotate(stack_b);
	write(1, "rb\n", 3);
}

void	rotate_all(t_stack *stack_a, t_stack *stack_b)
{
	rotate(stack_a);
	rotate(stack_b);
	write(1, "rr\n", 3);
}
