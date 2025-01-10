/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 07:54:02 by yannis            #+#    #+#             */
/*   Updated: 2025/01/10 01:27:52 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "checker.h"

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
    if (ft_strncmp(rule, "sa", ft_strlen(rule)) == 0)
        swap_a(stack_a);
    else if (ft_strncmp(rule, "sb", ft_strlen(rule)) == 0)
        swap_b(stack_b);
    else if (ft_strncmp(rule, "ss", ft_strlen(rule)) == 0)
        swap_all(stack_a, stack_b);
    else if (ft_strncmp(rule, "pa", ft_strlen(rule)) == 0)
        push_a(stack_a, stack_b);
    else if(ft_strncmp(rule, "pb", ft_strlen(rule)) == 0)
        push_b(stack_a, stack_b);
    else if(ft_strncmp(rule, "ra", ft_strlen(rule)) == 0)
        rotate_a(stack_a);
    else if(ft_strncmp(rule, "rb", ft_strlen(rule)) == 0)
        rotate_b(stack_b);
    else if(ft_strncmp(rule, "rr", ft_strlen(rule)) == 0)
        rotate_all(stack_a, stack_b);
    else if(ft_strncmp(rule, "rra", ft_strlen(rule)) == 0)
        reverse_rotate_a(stack_a);
    else if(ft_strncmp(rule, "rrb", ft_strlen(rule)) == 0)
        reverse_rotate_b(stack_a);
    else if(ft_strncmp(rule, "rrr", ft_strlen(rule)) == 0)
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
    char *line;
    
    stack_a.arr = malloc(argc * sizeof(int));
    stack_b.arr = malloc(argc * sizeof(int));

    stack_a.top = -1;
    stack_b.top = -1;
    
    argc = argc - 1;
    while (argc > 0)
    {
        stack_a.arr[++stack_a.top] = ft_atoi(argv[argc--]);
    }
    display_stacks(&stack_a, &stack_b);
    while ((line = get_next_line(0)) != NULL)
        do_rules(line, &stack_a, &stack_b);    
    display_stacks(&stack_a, &stack_b);
    printf("%s",check_stack_sort(&stack_a));
}

