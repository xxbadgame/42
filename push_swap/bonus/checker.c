/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 07:54:02 by yannis            #+#    #+#             */
/*   Updated: 2024/12/21 13:10:00 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "checker.h"
# include "../push_swap.h"

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

void do_rules(char *rule, t_stack *stack_a, t_stack *stack_b)
{
    ft_strtrim(rule, " \r\n");

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
        stack_a.arr[++stack_a.top] = ft_atoi(argv[argc]);
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

