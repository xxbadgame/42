/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:32:13 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/07 15:08:23 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int size_number(int n)
{
    int n_abs;
    int count;
    
    n_abs = (-(n) * (n < 0) + (n) * ((n) >= 0));
    while (n_abs >= 10)
    {
        n_abs /= 10;
        count++;
    }
    count++;
    return count;
}

char *allocate_number(int n)
{
    int size;
    char *nb_str;

    size = size_number(n);

    if (n >= 0)
    {
        nb_str = malloc(size + 1);
        nb_str[size] = '\0';
    }
    else
    {
        nb_str = malloc(size + 2);
        nb_str[size] = '\0';
        nb_str[0] = '-';
    }
    
    return nb_str;
}


char *ft_itoa(int n)
{
    unsigned int n_abs;
    char *nb_str;
    int size;

    n_abs = (-(n) * (n < 0) + (n) * ((n) >= 0));
    nb_str = allocate_number(n_abs);
    size = size_number(n);

    while (n_abs >= 10) {
        nb_str[size - 1] = n_abs % 10 + '0';
        n_abs /= 10;
        size--;
    }
    nb_str[size - 1] = n_abs % 10 + '0';

    return nb_str;
}


int main()
{
    int i;

    i = 42;

    printf("nbr : %s", ft_itoa(i));
}