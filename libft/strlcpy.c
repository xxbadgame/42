/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:18:34 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/05 15:34:59 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while(str[i])
        i++;
    return i;
}

unsigned int strlcpy(char *dest, const char *src, size_t size)
{
    int i;

    i = 0;
    if (size == 0)
        return (ft_strlen(src));
    while (src[i] && i < (size-1))
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = "\0";

    return (ft_strlen(src));
}