/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 15:17:17 by yannis            #+#    #+#             */
/*   Updated: 2025/01/14 17:34:52 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_median_numbers(t_stack *stack_a, t_stack *stack_b)
{
	int	median;
	int	i;
	int	new_min;

	i = 0;
	median = stack_a->arr[find_min_ind(stack_a)];
	while (i < (stack_a->top / 2 - 1))
	{
		new_min = stack_a->arr[closest_bigger_target(median, stack_a)];
		median = new_min;
		i++;
	}
	while (stack_a->top > 2)
	{
		push_b(stack_a, stack_b);
		if (stack_b->arr[stack_b->top] > median)
			rotate_b(stack_b);
	}
}

void	turk_sort(t_stack *stack_a, t_stack *stack_b)
{
	int	ind_target;
	int	ind_element;
	int	target;
	int	element;

	while (stack_b->top >= 0)
	{
		ind_element = cost_push(stack_a, stack_b);
		ind_target = closest_bigger_target(stack_b->arr[ind_element], stack_a);
		target = stack_a->arr[ind_target];
		element = stack_b->arr[ind_element];
		complete_rotation_one(stack_a, stack_b, ind_element, ind_target);
		complete_rotation_two(stack_a, ind_target, target);
		complete_rotation_three(stack_b, ind_element, element);
		push_a(stack_a, stack_b);
	}
	complete_rotation_four(stack_a);
}

void	push_swap(t_stack *stack_a, t_stack *stack_b)
{
	push_median_numbers(stack_a, stack_b);
	sort_three(stack_a);
	turk_sort(stack_a, stack_b);
}

int	main(int argc, char **argv)
{
	t_stack	stack_a;
	t_stack	stack_b;
	char	**spl_str;

	if (argc == 0)
		exit(0);
	stack_b.arr = malloc(argc * sizeof(int));
	if (!stack_b.arr)
		return (-1);
	spl_str = NULL;
	stack_a.top = -1;
	stack_b.top = -1;
	argc = argc - 1;
	if (create_stack(argc, argv, spl_str, &stack_a) == -1)
	{
		write(2, "Error\n", 6);
		free(stack_a.arr);
		free(stack_b.arr);
		exit(1);
	}
	push_swap(&stack_a, &stack_b);
	free(stack_a.arr);
	free(stack_b.arr);
	return (0);
}
