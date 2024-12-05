/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:55:17 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/12/05 21:39:00 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include "libft/libft.h"

int main(int argc, char **argv)
{
	t_list *stack_a;
	t_list *stack_b;
	
	t_list *move;
	int i;
	int size;

	i = 1;
	size = 0;
	stack_a = NULL;
	while (i < argc)
		ft_lstadd_back(&stack_a, ft_lstnew(argv[i++]));

	move = stack_a;
	while (move != NULL)
	{
		printf("content : %s\n", move->content);
		move = move->next;
		size++;
	}
	
	return (0);
}
