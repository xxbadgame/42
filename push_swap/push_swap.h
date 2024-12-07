/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 14:22:28 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/12/06 20:31:01 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "stdio.h"
# include "libft/libft.h"
#define MAX_SIZE 100

typedef struct s_stack 
{
	int arr[MAX_SIZE];
	int top;
} t_stack;

void push_a(t_stack *stack_a, t_stack *stack_b);
void push_b(t_stack *stack_a, t_stack *stack_b);

#endif