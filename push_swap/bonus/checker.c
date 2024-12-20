/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 07:54:02 by yannis            #+#    #+#             */
/*   Updated: 2024/12/20 23:19:31 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "checker.h"
# include "../push_swap.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

void do_rules(char *rule, t_stack *stack_a, t_stack *stack_b)
{
    if (rule == "sa")
        swap_a(stack_a);
    else if (rule == "sb")
        swap_b(stack_b);
    else if (rule == "ss")
        swap_all(stack_a, stack_b);
    else if (rule == "pa")
        push_a(stack_a, stack_a);
    else if(rule == "pb")
        push_b(stack_a, stack_b);
    else if(rule == "ra")
        rotate_a(stack_a);
    else if(rule == "rb")
        rotate_b(stack_b);
    else if(rule == "rr")
        rotate_all(stack_a, stack_b);
    else if(rule == "rra")
        reverse_rotate_a(stack_a);
    else if(rule == "rrb")
        reverse_rotate_b(stack_a);
    else if(rule == "rrr")
        reverse_rotate_all(stack_a, stack_b);
}

int main(int argc, char **argv)
{
    t_stack stack_a;
    t_stack stack_b;
    char *line;

    // remplir les stacks
    argc = argc - 1;
    while (argc > 0)
    {
        stack_a.arr[++stack_a.top] = atoi(argv[argc]);
        argc--;
    }

    // recevoir la sortie d'un push swap depuis la sortie standard avec un pipe et appliqué les regles
    while ((line = get_next_line(0)) != NULL)
        do_rules(line, &stack_a, &stack_b);    
    
    // vérifier si la stack A est trié.
}

