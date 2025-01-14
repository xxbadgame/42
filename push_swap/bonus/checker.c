/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 07:54:02 by yannis            #+#    #+#             */
/*   Updated: 2025/01/14 18:10:50 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	do_rules(char *rule, t_stack *stack_a, t_stack *stack_b)
{
	if (ft_strncmp(rule, "sa\n", ft_strlen(rule)) == 0)
		swap_a(stack_a);
	else if (ft_strncmp(rule, "sb\n", ft_strlen(rule)) == 0)
		swap_b(stack_b);
	else if (ft_strncmp(rule, "ss\n", ft_strlen(rule)) == 0)
		swap_all(stack_a, stack_b);
	else if (ft_strncmp(rule, "pa\n", ft_strlen(rule)) == 0)
		push_a(stack_a, stack_b);
	else if (ft_strncmp(rule, "pb\n", ft_strlen(rule)) == 0)
		push_b(stack_a, stack_b);
	else if (ft_strncmp(rule, "ra\n", ft_strlen(rule)) == 0)
		rotate_a(stack_a);
	else if (ft_strncmp(rule, "rb\n", ft_strlen(rule)) == 0)
		rotate_b(stack_b);
	else if (ft_strncmp(rule, "rr\n", ft_strlen(rule)) == 0)
		rotate_all(stack_a, stack_b);
	else if (ft_strncmp(rule, "rra\n", ft_strlen(rule)) == 0)
		reverse_rotate_a(stack_a);
	else if (ft_strncmp(rule, "rrb\n", ft_strlen(rule)) == 0)
		reverse_rotate_b(stack_a);
	else if (ft_strncmp(rule, "rrr\n", ft_strlen(rule)) == 0)
		reverse_rotate_all(stack_a, stack_b);
}

void	check_stack_sort(t_stack *stack_a)
{
	int	i;

	i = 0;
	while (i < stack_a->top)
	{
		if (stack_a->arr[i] < stack_a->arr[i + 1])
		{
			write(1, "KO", 2);
			exit(1);
		}
		i++;
	}
	write(1, "OK", 2);
}

int	init_stacks(t_stack *stack_a, t_stack *stack_b)
{
	stack_a->top = -1;
	stack_b->top = -1;
	return (0);
}

int	free_stacks(t_stack *stack_a, t_stack *stack_b)
{
	free(stack_a->arr);
	free(stack_b->arr);
	return (0);
}

int	main(int argc, char **argv)
{
	t_stack	stack_a;
	t_stack	stack_b;
	char	*line;
	char	**spl_str;

	if (argc == 0)
		exit(0);
	init_stacks(&stack_a, &stack_b);
	spl_str = NULL;
	stack_b.arr = malloc((argc - 1) * sizeof(int));
	if (!stack_b.arr)
		return (-1);
	if (create_stack(argc - 1, argv, spl_str, &stack_a) == -1)
	{
		write(2, "Error\n", 6);
		free_stacks(&stack_a, &stack_b);
		exit(1);
	}
	while ((line = get_next_line(0)) != NULL)
	{
		do_rules(line, &stack_a, &stack_b);
		free(line);
	}
	check_stack_sort(&stack_a);
	free_stacks(&stack_a, &stack_b);
}
