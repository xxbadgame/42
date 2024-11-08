/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strrchr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:51:14 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/05 17:22:47 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int ft_strlen(const char *str)
{
    int i;

    i = 0;
    while(str[i])
        i++;
    return i;
}

char *ft_strrchr(const char *s, int c)
{
    int i;

    i = ft_strlen(s) - 1;
    while (s[i])
    {
        if (s[i] == c)
            return ((char *)s+i);
        i--;
    }
    
    if (s[i] == '\0')
        return ((char *)s + i);
        
    return NULL;
}

int main()
{
    const char s[100] = "atestabt";
    
    printf("%s", ft_strrchr(s, 't'));
}