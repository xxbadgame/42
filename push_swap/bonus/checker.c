/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 07:54:02 by yannis            #+#    #+#             */
/*   Updated: 2024/12/21 01:26:39 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "checker.h"
# include "../push_swap.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <string.h>

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



void trim_rule(char *rule) {
    size_t len = strlen(rule);
    while (len > 0 && (rule[len - 1] == ' ' || rule[len - 1] == '\n' || rule[len - 1] == '\r')) {
        rule[--len] = '\0';
    }
}

void do_rules(char *rule, t_stack *stack_a, t_stack *stack_b)
{
    trim_rule(rule);

    if (strcmp(rule, "sa") == 0)
        swap_a(stack_a);
    else if (strcmp(rule, "sb") == 0)
        swap_b(stack_b);
    else if (strcmp(rule, "ss") == 0)
        swap_all(stack_a, stack_b);
    else if (strcmp(rule, "pa") == 0)
        push_a(stack_a, stack_b);
    else if(strcmp(rule, "pb") == 0)
        push_b(stack_a, stack_b);
    else if(strcmp(rule, "ra") == 0)
        rotate_a(stack_a);
    else if(strcmp(rule, "rb") == 0)
        rotate_b(stack_b);
    else if(strcmp(rule, "rr") == 0)
        rotate_all(stack_a, stack_b);
    else if(strcmp(rule, "rra") == 0)
        reverse_rotate_a(stack_a);
    else if(strcmp(rule, "rrb") == 0)
        reverse_rotate_b(stack_a);
    else if(strcmp(rule, "rrr") == 0)
        reverse_rotate_all(stack_a, stack_b);
}

char *check_stack_sort(t_stack *stack_a)
{
    int i;

    i = 0;
    while (i < stack_a->top)
    {
        if (stack_a->arr[i] < stack_a->arr[i + 1])
            return ("KO");
        i++;
    }
    return ("OK");
}

int main(int argc, char **argv)
{
    t_stack stack_a;
    t_stack stack_b;
    
    stack_a.top = -1;
    stack_b.top = -1;

    char *line;

    // remplir les stacks
    argc = argc - 1;
    while (argc > 0)
    {
        stack_a.arr[++stack_a.top] = atoi(argv[argc]);
        argc--;
    }

    display_stacks(&stack_a, &stack_b);

    // recevoir la sortie d'un push swap depuis la sortie standard avec un pipe et appliqué les regles
    while ((line = get_next_line(0)) != NULL)
        do_rules(line, &stack_a, &stack_b);    

    display_stacks(&stack_a, &stack_b);
    
    // vérifier si la stack A est trié.
    printf("%s",check_stack_sort(&stack_a));
    
}

