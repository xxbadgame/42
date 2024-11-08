/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:42:29 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/06 15:06:13 by ynzue-es         ###   ########.fr       */
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

char *ft_strjoin(char const *s1, char const *s2)
{
    int len_s1;
    int len_s2;
    char *strjoin;
    int i;
    int j;
    
    i = 0;
    j = 0;
    len_s1 = ft_strlen(s1);
    len_s2 = ft_strlen(s2);
    
    strjoin = malloc(len_s1 + len_s1);

    while (s1[i])
    {
        strjoin[i] = s1[i];
        i++;
    }
    
    while (s2[j])
    {
        strjoin[i] = s2[j];
        j++;
        i++;
    }
    strjoin[i] = '\0';
    return strjoin;
}

int main()
{
    char s1[] = "test1";
    char s2[] = "tes2";

    printf("%s", ft_strjoin(s1, s2));
   
}