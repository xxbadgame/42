/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:00:02 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/12/19 15:00:28 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "push_swap.h"

void complete_rotation_one(t_stack *stack_a, t_stack *stack_b, int ind_element, int ind_target)
{
    int target;
    int element;

    target = stack_a->arr[ind_target];
    element = stack_b->arr[ind_element];

    while (stack_b->arr[stack_b->top] != element && stack_a->arr[stack_a->top] != target)
    {
        if (ind_element >= (stack_b->top / 2) && ind_target >= (stack_a->top / 2))
            rotate_all(stack_a, stack_b);
        else if(ind_element < (stack_b->top / 2) && ind_target < (stack_a->top / 2))
            reverse_rotate_all(stack_a, stack_b); 
        else
            break;
    }
}

void complete_rotation_two(t_stack *stack_a, int ind_target, int target)
{
    while (stack_a->arr[stack_a->top] != target)
    {
        if (ind_target >= (stack_a->top / 2))
            rotate_a(stack_a);
        else
            reverse_rotate_a(stack_a);   
    }
}

void complete_rotation_three(t_stack *stack_b, int ind_element, int element)
{
    while (stack_b->arr[stack_b->top] != element)
    {
        if (ind_element >= (stack_b->top / 2))
            rotate_b(stack_b);
        else
            reverse_rotate_b(stack_b);
    }
}

void complete_rotation_four(t_stack *stack_a)
{
    int min_a;
    
    min_a = find_min_ind(stack_a);
    if (min_a < stack_a->top / 2)
    {
        while (min_a >= 0)
        {   
            reverse_rotate_a(stack_a);
            min_a--;
        }
    } 
    else
    {
        while (stack_a->top - min_a >= 0)
        {   
            rotate_a(stack_a);
            min_a++;
        }
    } 
}