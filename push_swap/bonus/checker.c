/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 07:54:02 by yannis            #+#    #+#             */
/*   Updated: 2024/12/19 16:23:05 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "checker.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int main()//int argc, char **argv)
{
    //t_stack stack_a;
    //t_stack stack_b;

    //char *line;
    printf("%s", get_next_line(0));
    // recevoir la sortie d'un push swap depuis la sortie standard avec un pipe
    //while ((line = get_next_line(0)) != NULL)
    //    printf("%s", line);    
    
    // les appliqués sur nos arguments de ./checker args
    /*
    argc = argc - 1;
    while (argc >= 1)
    {
        stack_a.arr[++stack_a.top] = atoi(argv[argc]);
        argc--;
    }
    push_swap(&stack_a, &stack_b);
    */
    // vérifier si la liste est trié.
}

