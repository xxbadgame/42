/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 15:17:17 by yannis            #+#    #+#             */
/*   Updated: 2024/12/19 08:44:58 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "push_swap.h"

void display_stacks(t_stack *stack_a, t_stack *stack_b)
{
	int i;
    int j;
    
	i = stack_a->top;
    j = stack_b->top;
	printf("-----------------------------------------------------------\n");
	while (i >= 0 || j >= 0)
    {
        if (i >= 0)
            printf("%d\t", stack_a->arr[i--]);
        else
            printf("\t");
        if (j >= 0)
            printf("%d\n", stack_b->arr[j--]);
        else
            printf("\n");
    }
	printf("_       _\n");
	printf("a       b\n");
}

int ft_abs(int value)
{
    return (value > 0) * value + (value < 0) * -value; 
}

int find_max_ind(t_stack *stack)
{
    int i;
    int ind;
    int max;

    i = 0;
    ind = 0;
    max = stack->arr[0];
    while (i <= stack->top)
    {
        if (stack->arr[i] > max)
        {
            max = stack->arr[i];
            ind = i;
        }    
        i++;
    }
    return (ind);
}

int find_min_ind(t_stack *stack)
{
    int i;
    int ind;
    int min;

    i = 0;
    ind = 0;
    min = stack->arr[0];
    while (i <= stack->top)
    {
        if (stack->arr[i] <= min)
        {
            min = stack->arr[i];
            ind = i;
        }    
        i++;
    }
    return (ind);
}

int closest_bigger_target(int value, t_stack *stack_a)
{
    int i;
    int ind_target;
    int min_diff;

    i = stack_a->top;
    ind_target = i;
    min_diff = INT_MAX;
    while (i >= 0)
    {
        if(stack_a->arr[i] > value && ft_abs(stack_a->arr[i] - value) < min_diff)
        {
            min_diff = ft_abs(stack_a->arr[i] - value);
            ind_target = i;
        }
        i--;
    }
    if (min_diff == INT_MAX)
        ind_target = find_min_ind(stack_a);

    return (ind_target);
}

void push_median_numbers(t_stack *stack_a, t_stack *stack_b)
{
    int median;
    int i;
    int new_min;

    i = 0;
    median = stack_a->arr[find_min_ind(stack_a)];
    while (i < (stack_a->top / 2 - 1))
    {
        new_min = stack_a->arr[closest_bigger_target(median, stack_a)];
        median = new_min;
        i++;
    }
    
    while (stack_a->top > 2)
    {
        push_b(stack_a,stack_b);
        if (stack_b->arr[stack_b->top] > median)
            rotate_b(stack_b);
    }
}


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

    min_cost = INT_MAX;
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

void complete_rotatation_one(t_stack *stack_a, t_stack *stack_b, int ind_element, int ind_target)
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

void complete_rotatation_two(t_stack *stack_a, t_stack *stack_b, int ind_element, int ind_target)
{
    int target;
    int element;

    //printf("reçu --> ind elem : %d, ind target : %d\n", ind_element, ind_target);
    target = stack_a->arr[ind_target];
    element = stack_b->arr[ind_element];

    while (stack_b->arr[stack_b->top] != element)
    {
        if (ind_element >= (stack_b->top / 2))
            rotate_b(stack_b);
        else
            reverse_rotate_b(stack_b);
    }
        
    while (stack_a->arr[stack_a->top] != target)
    {
        if (ind_target >= (stack_a->top / 2))
            rotate_a(stack_a);
        else
            reverse_rotate_a(stack_a);   
    }
}

void turk_sort(t_stack *stack_a, t_stack *stack_b)
{
    int ind_target;
    int ind_element;
    int target;
    int element;
    int min_a;
    
    while (stack_b->top >= 0)
    {
        ind_element = cost_push(stack_a, stack_b);
        ind_target = closest_bigger_target(stack_b->arr[ind_element], stack_a);
        target = stack_a->arr[ind_target];
        element = stack_b->arr[ind_element];

        //printf("base --> ind elem : %d, ind target : %d\n", ind_element, ind_target);
    
        //complete_rotatation_one(stack_a, stack_b, ind_element, ind_target);
        while (stack_b->arr[stack_b->top] != element && stack_a->arr[stack_a->top] != target)
        {
            if (ind_element >= (stack_b->top / 2) && ind_target >= (stack_a->top / 2))
                rotate_all(stack_a, stack_b);
            else if(ind_element < (stack_b->top / 2) && ind_target < (stack_a->top / 2))
                reverse_rotate_all(stack_a, stack_b); 
            else
                break;
        }

        //printf("enoyée --> ind elem : %d, ind target : %d\n", ind_element, ind_target);
        //complete_rotatation_two(stack_a, stack_b, ind_element, ind_target);

        
        while (stack_b->arr[stack_b->top] != element)
        {
            if (ind_element >= (stack_b->top / 2))
                rotate_b(stack_b);
            else
                reverse_rotate_b(stack_b);
        }
            
        while (stack_a->arr[stack_a->top] != target)
        {
            if (ind_target >= (stack_a->top / 2))
                rotate_a(stack_a);
            else
                reverse_rotate_a(stack_a);   
        }
        
        
        push_a(stack_a, stack_b);
    }
    
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


int main(int argc, char **argv)
{
    t_stack stack_a;
    t_stack stack_b;
    stack_a.top = -1;
    stack_b.top = -1;
   
    argc = argc - 1;
    while (argc >= 1)
    {
        stack_a.arr[++stack_a.top] = atoi(argv[argc]);
        argc--;
    }

    push_median_numbers(&stack_a, &stack_b);
    sort_three(&stack_a);
    turk_sort(&stack_a, &stack_b);
}