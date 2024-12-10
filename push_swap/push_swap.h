/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 14:22:28 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/12/11 00:36:41 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "stdio.h"
# include "unistd.h"
#define MAX_SIZE 1000

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
void sort_three(t_stack *stack_a);

#endif