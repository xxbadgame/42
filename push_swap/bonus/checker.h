/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 08:20:18 by yannis            #+#    #+#             */
/*   Updated: 2025/01/10 01:16:22 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H
# define MAX_SIZE 1000

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <string.h>
# include <stdio.h>

typedef struct s_stack 
{
	int *arr;
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