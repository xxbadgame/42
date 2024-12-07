/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:55:17 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/12/06 21:17:20 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "push_swap.h"

int display_stacks(t_stack *stack_a, t_stack *stack_b)
{
	int i;

	i = 0;

	printf("-----------------------------------------------------------\n");
	while(i <= stack_b->top || i <= stack_a->top)
	{
        printf("%d %d\n", stack_a->arr[i], stack_b->arr[i]);
		i++;
	}
	printf("_ _\n");
	printf("a b\n", stack_b->arr[i]);
}

int main(int argc, char **argv)
{
    t_stack stack_a;
    t_stack stack_b;

    stack_a.arr[0] = 5;
    stack_a.arr[1] = 2;
    stack_a.arr[2] = 3;
	stack_a.arr[3] = 9;

    stack_b.arr[0] = 0;
    stack_b.arr[1] = 0;
    stack_b.arr[2] = 0;
	stack_b.arr[3] = 0;

    stack_a.top = 3;
    stack_b.top = 3;

    display_stacks(&stack_a, &stack_b);

    return 0;
}


