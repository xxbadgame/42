/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   striteri.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:33:10 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/08 09:04:00 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void ft_toupper(unsigned int i, char *s)
{
    if (s[i] >= 97 && s[i] <= 122)
        s[i] -= 32;
}

void ft_striteri(char *s, void (*f)(unsigned int, char*))
{
    int i;

    i = 0;
    while (s[i])
    {
        f(i, s);
        i++;
    }
}

#include <stdio.h>

int main()
{
    char str[] = "testing"; 

    ft_striteri(str, ft_toupper);
    printf("apres : %s", str);
}