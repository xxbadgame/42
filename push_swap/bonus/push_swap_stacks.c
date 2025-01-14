/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_stacks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:24:26 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/01/14 17:04:56 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	len_stack_split(char **spl_str)
{
	int	i;

	i = 0;
	while (spl_str[i])
		i++;
	return (i);
}

int	spl_stack(t_stack *stack_a, char **spl_str, int len_spl)
{
	if (duplicates_error(spl_str, 1) == -1)
		return (-1);
	while (len_spl >= 0)
	{
		if (real_number_checker(spl_str[len_spl]) == -1)
			return (-1);
		if (ft_atol(spl_str[len_spl]) > INT_MAX
			|| ft_atol(spl_str[len_spl]) < INT_MIN)
			return (-1);
		else
			stack_a->arr[++stack_a->top] = ft_atol(spl_str[len_spl--]);
	}
	return (0);
}

int	argc_stack(t_stack *stack_a, char **argv, int argc)
{
	if (duplicates_error(argv, 0) == -1)
		return (-1);
	while (argc >= 1)
	{
		if (real_number_checker(argv[argc]) == -1)
			return (-1);
		if (ft_atol(argv[argc]) > INT_MAX || ft_atol(argv[argc]) < INT_MIN)
			return (-1);
		else
			stack_a->arr[++stack_a->top] = ft_atol(argv[argc--]);
	}
	return (0);
}

int	create_stack(int argc, char **argv, char **spl_str, t_stack *stack_a)
{
	int	len_spl;

	len_spl = 0;
	if (argc == 1)
	{
		spl_str = ft_split(argv[1], ' ');
		len_spl = len_stack_split(spl_str) - 1;
		stack_a->arr = malloc(len_stack_split(spl_str) * sizeof(long int));
		if (spl_stack(stack_a, spl_str, len_spl) == -1)
			return (-1);
	}
	else
	{
		stack_a->arr = malloc(argc * sizeof(long int));
		if (argc_stack(stack_a, argv, argc) == -1)
			return (-1);
	}
	return (0);
}
