/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:55:17 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/12/06 17:19:38 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "push_swap.h"

int main(void)
{
	t_stack *stack_a;
	int i;

	stack_a = malloc(sizeof(t_stack));
	i = 0;
	stack_a->top = 0;
	push(stack_a, 12);
	push(stack_a, 14);
	push(stack_a, 16);


	while(i < stack_a->top)
	{
		printf("%d\n",stack_a->arr[i]);
		i++;
	}
	free(stack_a);
}


