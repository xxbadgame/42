/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:58:23 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/01/14 16:58:02 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_abs(int value)
{
	return ((value > 0) * value + (value < 0) * -value);
}

int	find_max_ind(t_stack *stack)
{
	int	i;
	int	ind;
	int	max;

	i = 0;
	ind = 0;
	max = stack->arr[0];
	while (i <= stack->top)
	{
		if (stack->arr[i] > max)
		{
			max = stack->arr[i];
			ind = i;
		}
		i++;
	}
	return (ind);
}

int	find_min_ind(t_stack *stack)
{
	int	i;
	int	ind;
	int	min;

	i = 0;
	ind = 0;
	min = stack->arr[0];
	while (i <= stack->top)
	{
		if (stack->arr[i] <= min)
		{
			min = stack->arr[i];
			ind = i;
		}
		i++;
	}
	return (ind);
}

int	closest_bigger_target(int value, t_stack *stack_a)
{
	int	i;
	int	ind_target;
	int	min_diff;

	i = stack_a->top;
	ind_target = i;
	min_diff = __INT_MAX__;
	while (i >= 0)
	{
		if (stack_a->arr[i] > value && ft_abs(stack_a->arr[i]
				- value) < min_diff)
		{
			min_diff = ft_abs(stack_a->arr[i] - value);
			ind_target = i;
		}
		i--;
	}
	if (min_diff == __INT_MAX__)
		ind_target = find_min_ind(stack_a);
	return (ind_target);
}
