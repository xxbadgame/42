/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:40:41 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/06 12:45:04 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char *ft_strnstr(const char *big, const char *little, size_t len)
{
    int i;
    int j;
    
    i = 0;
    j = 0;

    if (*little == '\0')
        return (char *)big;
    
    while (len--)
    {
        j = 0;
        while (little[j] == big[i+j])
        {
            if (little[j + 1] == '\0')
                return ((char *)big + i);
            j++;  
        }
        i++; 
    }
    return NULL;
}

int main()
{
    char *big = "la phrase test";
    char *little = "";
    size_t len = 10;

    printf("%s",ft_strnstr(big, little, len));
}