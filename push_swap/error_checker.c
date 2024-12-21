/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:10:58 by yannis            #+#    #+#             */
/*   Updated: 2024/12/21 23:55:54 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "push_swap.h"
# include <stdio.h>

int ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while (*s1++ && *s2++)
    {
        if (*s1 != *s2)
            return (*s1 - *s2);
        i++;
    }
    return (*s1 - *s2);
}


int find_str(char *arg, char *str)
{
    int i;

    i = 0;
    while (arg[i] == str[i] && arg[i] && str[i])
    {
        if (arg[i + 1] == '\0' && str[i + 1] == '\0')
            return (1);
        i++;
    }
    return (0);
}

void duplicates_error(char **args)
{
    int i;
    int y;
    
    i = 1;
    while (args[i])
    {
        y = 1 + i;
        //printf("args x : %s\n", args[i]);
        while (args[y])
        {
            //printf("check args y : %s\n", args[y]);
            if (find_str(args[i], args[y]) == 1)
            {
                write(2, "Error\n", 6);
                exit(1);
            }
            y++;
        }   
        i++;
    }
}

int real_number_checker(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '-' && ft_isdigit(str[i + 1]))
            i++;
        else if (ft_isdigit(str[i]) == 0)
        {
            write(2, "Error\n", 6);
            exit(1);
        }
        else
            i++;
    }
    return (1);
}