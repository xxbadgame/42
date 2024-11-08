/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:39:09 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/05 16:50:54 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char *ft_strchr(const char *s, int c)
{
    while (*s++)
    {
        if (*s == c)
            return ((char *)s);
    }
    if (*s == '\0')
        return ((char *)s);
    return NULL;
}

int main()
{
    const char *s = "test";

    printf("%s",ft_strchr(s, 'e'));
}