/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swapV2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 15:17:17 by yannis            #+#    #+#             */
/*   Updated: 2024/12/15 00:50:58 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "push_swap.h"
#include <stdlib.h>
# include <limits.h>

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

void push_median_numbers(t_stack *stack_a, t_stack *stack_b)
{
    int len_stack_a;
    int median;

    len_stack_a = stack_a->top + 1; // car départ de zero
    if (len_stack_a % 2 == 0) // si c'est pair
        median = (stack_a->arr[(len_stack_a - 1) / 2] + stack_a->arr[(len_stack_a) / 2]) / 2;
    else
        median = stack_a->arr[(len_stack_a - 1) / 2];

    
    while (stack_a->top > 2)
    {
        push_b(stack_a,stack_b);
        if (stack_b->arr[stack_b->top] > median)
            rotate_b(stack_b);
    }
        
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

int ft_abs(int value)
{
    return (value > 0) * value + (value < 0) * -value; 
}

// return l'indice du closet smaller dans B
int closest_smaller_target(int value, t_stack *stack_b)
{
    int i;
    int ind_target;
    int min_diff;

    i = stack_b->top;
    ind_target = i;
    min_diff = INT_MAX;
    while (i >= 0)
    {
        if(stack_b->arr[i] <= value && ft_abs(value - stack_b->arr[i]) < min_diff)
        {
            min_diff = ft_abs(value - stack_b->arr[i]);
            ind_target = i;
        }
        i--;
    }
    
    if (min_diff == INT_MAX)
    {
        ind_target = find_max_ind(stack_b);
    }   

    return (ind_target);
}

// return l'indice du closet bigger dans A
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
    {
        ind_target = find_min_ind(stack_a);
    }   

    return (ind_target);
}


int cost_push(t_stack *stack_a, t_stack *stack_b)
{
    int min_cost;
    int target;
    int i_b;
    int ind_min_cost;
    int cost_a_top;
    int cost_b_top;
    int cost_a_bottom;
    int cost_b_bottom;
    int cost_a;
    int cost_b;
    int cost;

    min_cost = INT_MAX;
    ind_min_cost = 0;
    cost_a_top = 0;
    cost_b_top = 0;
    cost_a_bottom = 0;
    cost_b_bottom = 0;
    cost_a = 0;
    cost_b = 0;
    cost = 0;
    target = 0;
    i_b = stack_b->top;

    
    // l'objectif est de trouver l'élément de A le moins chère a envoyer dans B
    while (i_b >= 0)
    {

        // cost de b   
        if (i_b >= (stack_b->top / 2))
        {
            cost_b_top = stack_b->top - i_b;
            cost_b_bottom = 0;
        }
        else if (i_b < (stack_b->top / 2))
        {
            cost_b_top = 0;
            cost_b_bottom = i_b + 1;
        }


        target = closest_bigger_target(stack_b->arr[i_b], stack_a);

        // partie haute de la stack et cout moins chere
        if (target >= (stack_a->top / 2))
        {
            cost_a_top = stack_a->top - target;
            cost_a_bottom = 0;
        }
        // partie basse de la stack et cout moins chere
        else if (target < stack_a->top / 2)
        {
            cost_a_top = 0;
            cost_a_bottom = target + 1;
        }   
        
        
        if (cost_a_top > cost_b_top)
            cost = cost_a_top;
        else if (cost_a_top < cost_b_top)
            cost = cost_b_top;
        else
            cost = cost_a_top;

        if (cost_a_bottom > cost_b_bottom)
            cost += cost_a_bottom;
        else if (cost_a_bottom < cost_b_bottom)
            cost += cost_b_bottom;
        else
            cost += cost_a_bottom;

        
        if (cost < min_cost)
        {
            min_cost = cost;
            ind_min_cost = i_b;
        }
        

        i_b--;
    }

   
    return (ind_min_cost);
}

// ajouter les rrr et les rr dans le cas ou c'est en commun

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
        
        
        while (stack_b->arr[stack_b->top] != element && stack_a->arr[stack_a->top] != target)
        {
            if (ind_element >= (stack_b->top / 2) && ind_target >= (stack_a->top / 2))
                rotate_all(stack_a, stack_b);
            else if(ind_element < (stack_b->top / 2) && ind_target < (stack_a->top / 2))
                reverse_rotate_all(stack_a, stack_b); 
            else
                break;
        }

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
    
    while (min_a >= 0)
    {   
        reverse_rotate_a(stack_a);
        min_a--;
    }
    
}


int main(int argc, char **argv)
{
    t_stack stack_a, stack_b;
    stack_a.top = -1;
    stack_b.top = -1;
   
    argc = argc - 1;
    while (argc >= 1)
    {
        //printf("argc :%d\n", argc);
        //printf("nbr : %d\n", atoi(argv[argc]));
        stack_a.arr[++stack_a.top] = atoi(argv[argc]);
        argc--;
    }

    push_median_numbers(&stack_a, &stack_b);
    sort_three(&stack_a);
    turk_sort(&stack_a, &stack_b);
    
    //push_2_numbers(&stack_a, &stack_b);
    //display_stacks(&stack_a, &stack_b);
    //cost_push(&stack_a, &stack_b);

    //printf("closest smaller : %d\n", closest_smaller_target(2, &stack_a));
    //printf("indice du max : %d\n", find_max_ind(&stack_a));
    
    
}