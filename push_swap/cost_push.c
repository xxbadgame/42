/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:56:21 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/12/21 13:07:17 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "push_swap.h"

void cost_calculate(int i_b, t_stack *stack_a, t_stack *stack_b, t_cost_push *cost)
{
    int target;

    if (i_b >= (stack_b->top / 2))
        cost->b_top = stack_b->top - i_b;
    else if (i_b < (stack_b->top / 2))
        cost->b_bottom = i_b + 1;
    target = closest_bigger_target(stack_b->arr[i_b], stack_a);
    if (target >= (stack_a->top / 2))
        cost->a_top = stack_a->top - target;
    else if (target < stack_a->top / 2)
        cost->a_bottom = target + 1;      
}

int cost_logic(int cost_a_top, int cost_b_top, int cost_a_bottom, int cost_b_bottom)
{
    int cost;
    
    cost = 0;
    if (cost_a_top >= cost_b_top)
        cost = cost_a_top;
    else if (cost_a_top < cost_b_top)
        cost = cost_b_top;
    if (cost_a_bottom >= cost_b_bottom)
        cost += cost_a_bottom;
    else if (cost_a_bottom < cost_b_bottom)
        cost += cost_b_bottom;
    return(cost);
}

int cost_push(t_stack *stack_a, t_stack *stack_b)
{
    int min_cost;
    int i_b;
    int ind_min_cost;
    t_cost_push cost;

    min_cost = __INT_MAX__;
    ind_min_cost = 0;
    i_b = stack_b->top;
    while (i_b >= 0)
    {
        cost.a_top = 0;
        cost.b_top = 0;
        cost.a_bottom = 0;
        cost.b_bottom = 0;
        cost_calculate(i_b, stack_a, stack_b, &cost);
        if (cost_logic(cost.a_top, cost.b_top, cost.a_bottom, cost.b_bottom) < min_cost)
        {
            min_cost = cost_logic(cost.a_top, cost.b_top, cost.a_bottom, cost.b_bottom);
            ind_min_cost = i_b;
        }
        i_b--;
    }
    return (ind_min_cost);
}