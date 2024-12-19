/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 14:22:28 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/12/19 15:31:00 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
#define MAX_SIZE 1000

typedef struct s_stack 
{
	int arr[MAX_SIZE];
	int top;
} t_stack;

typedef struct s_cost_push
{
	int a_top;
    int b_top;
    int a_bottom;
    int b_bottom;
} t_cost_push;


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
void push_swap(t_stack *stack_a, t_stack *stack_b);
void display_stacks(t_stack *stack_a, t_stack *stack_b);
int ft_abs(int value);
int find_max_ind(t_stack *stack);
int find_min_ind(t_stack *stack);
int closest_bigger_target(int value, t_stack *stack_a);
void cost_calculate(int i_b, t_stack *stack_a, t_stack *stack_b, t_cost_push *cost);
int cost_logic(int cost_a_top, int cost_b_top, int cost_a_bottom, int cost_b_bottom);
int cost_push(t_stack *stack_a, t_stack *stack_b);
void complete_rotation_one(t_stack *stack_a, t_stack *stack_b, int ind_element, int ind_target);
void complete_rotation_two(t_stack *stack_a, int ind_target, int target);
void complete_rotation_three(t_stack *stack_b, int ind_element, int element);
void complete_rotation_four(t_stack *stack_a);



#endif