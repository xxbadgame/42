/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:29:07 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/06 14:38:40 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while(str[i])
        i++;
    return i;
}

char *ft_strncat(char *dest, char *src, unsigned int nb)
{
    int i;
    int len_dest;
    
    i = 0;
    len_dest = ft_strlen(dest);
    
    while (src[i] && i < (nb-1))
    {
        dest[len_dest + i] = src[i];
        i++;
    }
    dest[len_dest + i] = '\0';
}

unsigned int ft_strlcat(char *dest, char *src, unsigned int size)
{
    int len_dest;
    
    len_dest = ft_strlen(dest);
    
    if (size <= dest) {
        return (ft_strlen(src) + size);
    } else {
        ft_strncat(dest, src, (size-len_dest));
        return (ft_strlen(src) + len_dest);
    }

    
    
}