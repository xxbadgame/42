/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 14:22:28 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/12/09 12:26:27 by ynzue-es         ###   ########.fr       */
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
void swap_a(t_stack *stack_a);
void swap_b(t_stack *stack_b);
void swap_all(t_stack *stack_a, t_stack *stack_b);
void rotate_a(t_stack *stack_a);
void rotate_b(t_stack *stack_b);
void rotate_all(t_stack *stack_a, t_stack *stack_b);
void reverse_rotate_a(t_stack *stack_a);
void reverse_rotate_b(t_stack *stack_b);
void reverse_rotate_all(t_stack *stack_a, t_stack *stack_b);

#endif