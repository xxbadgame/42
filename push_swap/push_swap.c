/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:55:17 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/12/09 17:04:50 by ynzue-es         ###   ########.fr       */
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

void find_cheapest_number(t_stack *stack_a, t_stack *stack_b, int min, int max, int ind_min, int ind_max)
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


int main(int argc, char **argv)
{
    t_stack *stack_a;
    t_stack *stack_b;

    push_2_numbers(&stack_a, &stack_b);
    if (stack_b->arr[stack_b->top] > stack_b->arr[stack_b->top - 1])
        find_cheapest_number(stack_a, stack_b, stack_b->arr[stack_b->top - 1], stack_b->arr[stack_b->top]);
    else
        find_cheapest_number(stack_a, stack_b, stack_b->arr[stack_b->top], stack_b->arr[stack_b->top - 1]);
}


