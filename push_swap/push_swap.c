/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:55:17 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/12/12 15:57:38 by ynzue-es         ###   ########.fr       */
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
	while(1)
	{
        if (j < 0 && i < 0)
            break;
        if (i >= 0)
            printf("%d", stack_a->arr[i]);
        if (j >= 0 && i < 0)
            printf("  %d\n", stack_b->arr[j]);
        else if (j >= 0)
            printf(" %d\n", stack_b->arr[j]);
        if (j < 0)
            printf("\n");
		i--;
        j--;
	}
	printf("_ _\n");
	printf("a b\n");
}

void push_2_numbers(t_stack *stack_a, t_stack *stack_b)
{
    push_b(stack_a, stack_b);
    push_b(stack_a, stack_b);
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
        if(stack_a->arr[i] >= value && ft_abs(stack_a->arr[i] - value) < min_diff)
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
    int cost_a_top;
    int cost_b_top;
    int cost_a_bottom;
    int cost_b_bottom;
    int cost_a;
    int cost_b;
    int cost;
    int min_cost;
    int close_small_index ;
    int i_a;
    int i_b;
    int ind_min_cost;

    min_cost = INT_MAX;
    ind_min_cost = 0;
    cost = 0;
    cost_a_top = 0;
    cost_b_top = 0;
    cost_a_bottom = 0;
    cost_b_bottom = 0;
    cost_a = 0;
    cost_b = 0;
    i_a = stack_a->top;
    i_b = stack_b->top;
    
    // l'objectif est de trouver l'élément de A le moins chère a envoyer dans B
    while (i_a >= 0)
    {
        // cost de a
        if (i_a >= (stack_a->top / 2))
        {
            cost_a_top = stack_a->top - i_a;
            cost_a_bottom = 0;
        }
        // partie basse de la stack et cout moiint cost_a_top;
    int cost_b_top;
    int cost_a_bottom;
    int cost_b_bottom;
        
        close_small_index = closest_smaller_target(stack_a->arr[i_a], stack_b);

        // partie haute de la stack et cout moins chere
        if (close_small_index >= (stack_b->top / 2))
        {
            cost_b_top = stack_b->top - close_small_index;
            cost_b_bottom = 0;
        }
        // partie basse de la stack et cout moins chere
        else if (close_small_index < stack_b->top / 2)
        {
            cost_b_top = 0;
            cost_b_bottom = close_small_index + 1;
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

        //cost_a = cost_a_top + cost_a_bottom;
        //cost_b = cost_b_top + cost_b_bottom;
        
        //printf("cost_a_top : %d\n", cost_a_top);
        //printf("cost_a_bottom : %d\n", cost_a_bottom);
        //printf("cost_b_top : %d\n", cost_b_top);
        //printf("cost_b_bottom : %d\n", cost_b_bottom);
        //printf("element stack : %d | target : %d | cost : %d\n", stack_a->arr[i_a] , close_small_index , cost);

        if (cost < min_cost)
        {
            min_cost = cost;
            ind_min_cost = i_a;
        }
        

        i_a--;
    }
   
    // return l'indice de l'élément a push
    return (ind_min_cost);
}


// ajouter les rrr et les rr dans le cas ou c'est en commun

void turk_sort(t_stack *stack_a, t_stack *stack_b)
{
    int ind_elem_push;
    int element;
    int ind_target;
    int target;
    int test;
    int i_b;
    int min_a;

    test = 0;
    push_2_numbers(stack_a, stack_b);
    
    
    // tant qu il y a au mois 3 element dans A
    while (stack_a->top > 2) // stack_a->top > 2
    {
        ind_elem_push = cost_push(stack_a, stack_b);
        element = stack_a->arr[ind_elem_push];
        ind_target = closest_smaller_target(element, stack_b);
        target = stack_b->arr[ind_target];

        /*
        // Les deux en même temps
        while (stack_a->arr[stack_a->top] != element && stack_b->arr[stack_b->top] != target)
        {
            if (ind_elem_push >= stack_a->top / 2 && ind_target >= stack_b->top / 2)
                rotate_all(stack_a, stack_b);
            else
                reverse_rotate_all(stack_a, stack_b);

            if (ind_elem_push >= stack_a->top / 2 && stack_b->arr[stack_b->top] == target)
                rotate_a(stack_a);
            else if (ind_elem_push < stack_a->top / 2 && stack_b->arr[stack_b->top] == target)
                reverse_rotate_a(stack_a);

            if (ind_target >= stack_b->top / 2 && stack_a->arr[stack_a->top] != element)
                rotate_b(stack_b);
            else if (ind_target < stack_b->top / 2 && stack_a->arr[stack_a->top] != element)
                reverse_rotate_b(stack_b);
        }
        */
        
        // La stack A
        while (stack_a->arr[stack_a->top] != element)
        {
            if (ind_elem_push >= stack_a->top / 2)
                rotate_a(stack_a);
            else
                reverse_rotate_a(stack_a);
        }
        
        // mettre la target de B en haut
        while (stack_b->arr[stack_b->top] != target)
        {
            if (ind_target >= stack_b->top / 2)
                rotate_b(stack_b);
            else
                reverse_rotate_b(stack_b);
        }
        

        // push de A a B
        push_b(stack_a, stack_b);

        //display_stacks(stack_a, stack_b);
        
    }   

    
    // apres ca on a nos element trier dans B, il en reste 3 dans A qu on tri
    sort_three(stack_a);


    
    // on remet les element de B dans A en verifiant si il y un des elements deja dans A qu on rotate pour tout mettre dans l ordre
    i_b = stack_b->top;
    while (i_b >= 0)
    {
        ind_target = closest_bigger_target(stack_b->arr[i_b], stack_a);
        target = stack_a->arr[ind_target];

        //printf("etape de B");
        //display_stacks(stack_a, stack_b);
        //printf("target : %d\n", target);
        
        while (stack_a->arr[stack_a->top] != target)
        {
            if (ind_target >= stack_a->top / 2)
                rotate_a(stack_a);
            else
                reverse_rotate_a(stack_a);
        }

        push_a(stack_a, stack_b);

        i_b--; 
    }
    
    
    min_a = find_min_ind(stack_a);
    //printf("index du min : %d\n", min_a);
    
    while (min_a >= 0)
    {   
        //printf("min a : %d\n", min_a);
        reverse_rotate_a(stack_a);
        /*if (min_a >= stack_a->top / 2)
            rotate_a(stack_a);
        else
            reverse_rotate_a(stack_a);
        */
        min_a--;
    }
}


int main(int argc, char **argv)
{
    t_stack stack_a, stack_b;
    stack_a.top = -1;
    stack_b.top = -1;
   
    /*
    stack_a.arr[++stack_a.top] = -38;
    stack_a.arr[++stack_a.top] = 85;
    stack_a.arr[++stack_a.top] = 9;
    stack_a.arr[++stack_a.top] = 12;
    stack_a.arr[++stack_a.top] = 6;
    stack_a.arr[++stack_a.top] = 5;
    stack_a.arr[++stack_a.top] = 7;
    stack_a.arr[++stack_a.top] = 42;
    stack_a.arr[++stack_a.top] = 57;
    stack_a.arr[++stack_a.top] = 58;
    stack_a.arr[++stack_a.top] = 35;
    stack_a.arr[++stack_a.top] = 49;
    stack_a.arr[++stack_a.top] = 57;
    */
   
    argc = argc - 1;
    while (argc >= 1)
    {
        //printf("argc :%d\n", argc);
        //printf("nbr : %d\n", atoi(argv[argc]));
        stack_a.arr[++stack_a.top] = atoi(argv[argc]);
        argc--;
    }

    //display_stacks(&stack_a, &stack_b);
    turk_sort(&stack_a, &stack_b);
    //display_stacks(&stack_a, &stack_b);
    
    //push_2_numbers(&stack_a, &stack_b);
    //display_stacks(&stack_a, &stack_b);
    //cost_push(&stack_a, &stack_b);

    //printf("closest smaller : %d\n", closest_smaller_target(2, &stack_a));
    //printf("indice du max : %d\n", find_max_ind(&stack_a));
    
    
}


