/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:55:17 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/12/10 18:06:33 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "push_swap.h"
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

/*
void find_cheapest_number(t_stack *stack_a, t_stack *stack_b, int ind_min, int ind_max)
{
    int current;
    int cost;
    int smaller_diff;
    int target;

    current = stack_a->arr[stack_a->top];

    // trouver la target par rapport au current
    if (current - max < current - min)
        target = max;
    else if (current - max > current - min)
        target = min;
    else
        target = max;

    // Calcul la diff des indices, pour simuler le nombre de rota de stack_a et le nombre de rota de stack_b, a partir du current et pas faire tous les currents de la liste, on en test 4 maxi
    
    // on prend le cost minimum, et la suite d instruction enregistrer avec 
}
*/

/*
// Il faut trouver l'indice le plus rapide sois depuis en haut sois depuis en bas car par exemple si c'est juste en dessous du top on fera juste une opération
int find_min_ind(t_stack *stack)
{
    int i;
    int ind;
    int min;

    i = 0;
    ind = 0;
    min = stack->arr[0];
    while (i < stack->top)
    {
        if (stack->arr[i] < min)
        {
            min = stack->arr[i];
            ind = i;
        }  
        i++;  
    }
 
    return (ind);
}
*/

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
        if(stack_b->arr[i] < value && (value - stack_b->arr[i]) < min_diff)
        {
            min_diff = value - stack_b->arr[i];
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
        // partie basse de la stack et cout moins chere
        else if (i_a < (stack_a->top / 2))
        {
            cost_a_top = 0;
            cost_a_bottom = stack_a->top - i_a + 1;
        }            
        
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
            cost += cost_b_top;
        else
            cost += cost_a_bottom;

        //cost_a = cost_a_top + cost_a_bottom;
        //cost_b = cost_b_top + cost_b_bottom;
        
        printf("cost_a_top : %d\n", cost_a_top);
        printf("cost_a_bottom : %d\n", cost_a_bottom);
        printf("cost_b_top : %d\n", cost_b_top);
        printf("cost_b_bottom : %d\n", cost_b_bottom);
        printf("element stack : %d | target : %d | cost : %d\n", stack_a->arr[i_a] , close_small_index , cost);

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


void turk_sort(t_stack *stack_a, t_stack *stack_b)
{
    int ind_elem_push;
    int element;
    int ind_target;
    int target;
    int test;

    test = 0;
    push_2_numbers(stack_a, stack_b);

    printf("Base-------------------------------");
    display_stacks(stack_a, stack_b);

    
    // tant au il y a au mois 3 element dans A
    while (stack_a->top > 2) // stack_a->top > 2
    {
        ind_elem_push = cost_push(stack_a, stack_b);
        element = stack_a->arr[ind_elem_push];
        printf("element a envoyer %d\n", stack_a->arr[ind_elem_push]);
        ind_target = closest_smaller_target(stack_a->arr[ind_elem_push], stack_b);
        target = stack_b->arr[ind_target];
        printf("Target %d\n", target);

        //printf("element push : %d, target : %d\n", i,target);

        // mettre l element de A en haut si il n y est pas

        while (stack_a->arr[stack_a->top] != element) //&& i >= (stack_a->top / 2))
        {
            if (ind_elem_push >= stack_a->top / 2)
                rotate_a(stack_a);
            else
                reverse_rotate_a(stack_a);
        }
        
        // mettre la target de B en haut
        while (stack_b->arr[stack_b->top] != target) //&& i >= (stack_a->top / 2))
        {
            if (ind_target >= stack_b->top / 2)
                rotate_b(stack_b);
            else
                reverse_rotate_b(stack_b);
        }

        // push de A a B
        push_b(stack_a, stack_b);

        display_stacks(stack_a, stack_b);
        
    }   

    // apres ca on a nos element trier dans B, il en reste 3 dans A qu on tri

    // on remet les element de B dans A en verifiant si il y un des elements deja dans A qu on rotate pour tout mettre dans l ordre
     
}


int main(int argc, char **argv)
{
    t_stack stack_a;
    t_stack stack_b;

    stack_a.top = -1;
    stack_b.top = -1;

    stack_a.arr[++stack_a.top] = 8;
    stack_a.arr[++stack_a.top] = 4;
    stack_a.arr[++stack_a.top] = 9;
    stack_a.arr[++stack_a.top] = 3;
    stack_a.arr[++stack_a.top] = 6;
    stack_a.arr[++stack_a.top] = 1;
    stack_a.arr[++stack_a.top] = 7;
    stack_a.arr[++stack_a.top] = 2;
    stack_a.arr[++stack_a.top] = 5;

    
    turk_sort(&stack_a, &stack_b);
    
    display_stacks(&stack_a, &stack_b);
    //push_2_numbers(&stack_a, &stack_b);
    //display_stacks(&stack_a, &stack_b);
    //cost_push(&stack_a, &stack_b);

    //printf("closest smaller : %d\n", closest_smaller_target(2, &stack_a));
    //printf("indice du max : %d\n", find_max_ind(&stack_a));
    
    
}


