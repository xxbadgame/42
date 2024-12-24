/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 10:38:26 by yannis            #+#    #+#             */
/*   Updated: 2024/12/24 10:52:49 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

long int str_to_hexa(char *str)
{
	int i;
	long int result;

	result = 0;
    i = 0;

    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		i = 2;
        
	while ((str[i] >= '0' && str[i] <= '9') 
        || (str[i] >= 'A' && str[i] <= 'F') 
        || (str[i] >= 'a' && str[i] <= 'f'))
	{
	if (str[i] >= '0' && str[i] <= '9')
		    result = result * 16 + (str[i] - '0');
        else if (str[i] >= 'A' && str[i] <= 'F')
            result = result * 16 + (str[i] - 'A' + 10);
        else if (str[i] >= 'a' && str[i] <= 'f')
            result = result * 16 + (str[i] - 'a' + 10);
		i++;
	}
    return (result);
}