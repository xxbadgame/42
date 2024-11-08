/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:52:57 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/06 13:32:05 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int ft_strlen(const char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return i; 
}

char *ft_strdup(const char *s)
{
    int size;
    char *str; 
    char *ptr;

    size = ft_strlen(s);    
    str = malloc(size + 1);
    ptr = str;
    while (*s) {
        *str++ = *s++;
    }
    str = 0;
    return (ptr);
}

int main(int argc, char **argv) {
    char *str;

    str = ft_strdup(argv[1]);
    printf("%s\n", str);
    return (0);
}