/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:58:38 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/05 18:18:57 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int ft_atoi(char *str)
{
    int i;
    int sign;
    int result;

    i = 0;
    sign = 1;
    result = 0;
    if (str[0] == '-')
        sign *= -1;
    else if (str[0] == '+' || str[0] >= '0' && str[0] <= '9')
    {
        while (str[i])
        {
            result *= 10;
            result += str[i] - 48;
            i++;
        }
        return (result * sign);
    }
    
    return 0;
}

int main()
{
    char *str = "123";

    printf("en int : %d", ft_atoi(str) + 2);
}