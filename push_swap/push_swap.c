/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:55:17 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/12/10 02:41:52 by yannis           ###   ########.fr       */
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
    while (i < stack->top)
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
        if(stack_b->arr[i] <= value && (stack_b->arr[i] - value) < min_diff)
        {
            min_diff = stack_b->arr[i] - value;
            ind_target = i;
        }
        i--;
    }
    if (min_diff == INT_MAX)
        ind_target = find_max_ind(stack_b);
        
    return (ind_target);
}


int cost_push(t_stack *stack_a, t_stack *stack_b)
{
    int cost_temp_a;
    int cost_temp_b;
    int cost;

    int i_a;
    int i_b;

    cost = INT_MAX;
    cost_temp_a = INT_MAX;
    cost_temp_b = INT_MAX;
    i_a = stack_a->top;
    i_b = stack_b->top;
    // l'objectif est de trouver l'élément de A le moins chère a envoyer dans B

    while (i_a > 0)
    {
        if (i_a > stack_a->top / 2 && (stack_a->top - i_a) < cost_temp_a)
            cost_temp_a = stack_a->top - i_a;
        else if (i_a < stack_a->top / 2 && (stack_a->top - i_a) < cost_temp_a)
            cost_temp_a = i_a;

        int close_small_index ;

        close_small_index = closest_smaller_target(stack_a->arr[i_a], stack_b);

        if (close_small_index > stack_a->top / 2 && (stack_b->top - close_small_index) < cost_temp_b)
            cost_temp_b = stack_b->top - close_small_index;
        else if (close_small_index < stack_a->top / 2 && (stack_b->top - close_small_index) < cost_temp_b)
            cost_temp_b = i_b;


        printf("cost temp a : %d", cost_temp_a);
        printf("cost temp b : %d", cost_temp_b);

        // proposition cost combiner
        if (cost_temp_a > cost_temp_b && (cost_temp_a - cost_temp_b) < cost)
            cost = cost_temp_a - cost_temp_b;
        else if(cost_temp_a < cost_temp_b && (cost_temp_a - cost_temp_b) > cost)
            cost = cost_temp_b - cost_temp_a;
        else 
            cost = stack_a->top - i_a;
            
        i_a--;
    }
   
    printf("cost : %d", cost);
    // return l'indice de l'élément a push
    return (0);
}


int main(int argc, char **argv)
{
    t_stack stack_a;
    t_stack stack_b;

    stack_a.top = -1;
    stack_b.top = -1;

    stack_a.arr[++stack_a.top] = 5;
    stack_a.arr[++stack_a.top] = 3;
    stack_a.arr[++stack_a.top] = 4;
    stack_a.arr[++stack_a.top] = 2;
    stack_a.arr[++stack_a.top] = 9;
    stack_a.arr[++stack_a.top] = 2;
    stack_a.arr[++stack_a.top] = 8;
    stack_a.arr[++stack_a.top] = 1;

    display_stacks(&stack_a, &stack_b);
    push_2_numbers(&stack_a, &stack_b);
    display_stacks(&stack_a, &stack_b);
    
    cost_push(&stack_a, &stack_b);
}


