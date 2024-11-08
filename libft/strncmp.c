/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strncmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:23:29 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/05 17:36:35 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int ft_strncmp(const char *s1, const char *s2)
{
    int i;

    i = 0;
    while (s1[i] && s1[i] < s2[i])
    {
        if (s1[i] == s2[i])
            i++;
        return (s1[i] - s2[i]);
    }
    return (s1[i] - s2[i]);
}

int main()
{
    char s1[] = "b";
    char s2[] = "a";

    printf("%d",ft_strncmp(s1, s2));
}
