/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 07:54:02 by yannis            #+#    #+#             */
/*   Updated: 2025/01/16 13:59:25 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	do_rules(char *rule, t_stack *stack_a, t_stack *stack_b)
{
	if (ft_strncmp(rule, "sa\n", 3) == 0)
		swap_a(stack_a);
	else if (ft_strncmp(rule, "sb\n", 3) == 0)
		swap_b(stack_b);
	else if (ft_strncmp(rule, "ss\n", 3) == 0)
		swap_all(stack_a, stack_b);
	else if (ft_strncmp(rule, "pa\n", 3) == 0)
		push_a(stack_a, stack_b);
	else if (ft_strncmp(rule, "pb\n", 3) == 0)
		push_b(stack_a, stack_b);
	else if (ft_strncmp(rule, "ra\n", 3) == 0)
		rotate_a(stack_a);
	else if (ft_strncmp(rule, "rb\n", 3) == 0)
		rotate_b(stack_b);
	else if (ft_strncmp(rule, "rr\n", 3) == 0)
		rotate_all(stack_a, stack_b);
	else if (ft_strncmp(rule, "rra\n", 4) == 0)
		reverse_rotate_a(stack_a);
	else if (ft_strncmp(rule, "rrb\n", 4) == 0)
		reverse_rotate_b(stack_a);
	else if (ft_strncmp(rule, "rrr\n", 4) == 0)
		reverse_rotate_all(stack_a, stack_b);
	else
		return (-1);
	return (0);
}

int	check_stack_sort(t_stack *stack_a)
{
	int	i;

	i = 0;
	while (i < stack_a->top)
	{
		if (stack_a->arr[i] < stack_a->arr[i + 1])
		{
			write(1, "KO\n", 3);
			return (-1);
		}
		i++;
	}
	if (stack_a->top > -1)
		write(1, "OK\n", 3);
	return (0);
}

int	free_stacks(t_stack *stack_a, t_stack *stack_b)
{
	free(stack_a->arr);
	free(stack_b->arr);
	return (0);
}

int	rules_writer(t_stack *stack_a, t_stack *stack_b)
{
	char	*line;

	while (1)
	{
		line = get_next_line(0);
		if (line == NULL)
		{
			free(line);
			break ;
		}
		if (do_rules(line, stack_a, stack_b) == -1)
		{
			write(2, "Error\n", 6);
			return (free(line), -1);
		}
		free(line);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_stack	stack_a;
	t_stack	stack_b;

	stack_a.top = -1;
	stack_b.top = -1;
	if (argc == 0)
		exit(0);
	if (create_stack(argc - 1, argv, &stack_a, &stack_b) == -1)
	{
		write(2, "Error\n", 6);
		free_stacks(&stack_a, &stack_b);
		exit(1);
	}
	if (rules_writer(&stack_a, &stack_b) != -1)
		check_stack_sort(&stack_a);
	free_stacks(&stack_a, &stack_b);
}
