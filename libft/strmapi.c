/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strmapi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:11:39 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/07 16:48:57 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int ft_strlen(char const *s)
{
    int i;

    i = 0;
    while (s[i])
        i++;
    return i;
}

char *ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
    unsigned int i;
    char *str;

    i = 0;

    str = malloc(ft_strlen(s) + 1);
    
    while (s[i])
    {
        str[i] = f(i, s[i]);
        i++;
    }
    str[i] = '\0';

    return str;
}

char ft_toupper(unsigned int i, char c)
{
    if (c >= 97 && c <= 122)
        c -= 32;
    return c;
}

int main()
{
    char *str = "testing"; 

    printf("result : %s",ft_strmapi(str, ft_toupper));
}