/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:48:42 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/06 17:03:48 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int ft_strlen(char const *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return i;
}

int is_charset(char c,char const *set)
{
    int i;

    i = 0;
    while (set[i])
    {
        if (set[i] == c)
            return 1;
        i++;
    }
    return 0;
}

int startIndex(char const *str, char const *set)
{
    int i;
    int size;

    i = 0;
    size = ft_strlen(str);
    while (is_charset(str[i], set) && i < size)
        i++;
    return i;
}

int endIndex(char const *str, char const *set)
{
    int i;

    i = ft_strlen(str) - 1;
    while (is_charset(str[i], set) && i >= 0)
        i--;
    return i;
}

char *ft_strtrim(char const *s1, char const *set)
{
    int start;
    int end;
    int i;
    char *copy_s1;

    i = 0;
    start = startIndex(s1, set);
    end = endIndex(s1, set);

    printf("start : %d\n", start);
    printf("end : %d", end);
    
    if (start > end) {
        copy_s1 = malloc(1);
        copy_s1[i] = '\0';
        if (!copy_s1)
            return NULL;
    
    } else {
        copy_s1 = malloc((end - start)+2);
        if (!copy_s1)
            return NULL;
        while (start <= end)
        {
            copy_s1[i] = s1[start];
            i++;
            start++;
        }
    }
        
    return (copy_s1);
}

int main()
{
    char *str = "  test  ";
    char *set = " ";

    printf("result :%s",ft_strtrim(str, set));
}