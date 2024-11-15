/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:14:16 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/15 17:40:24 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "../libft/libft.h"
#include <stdio.h>

int	ft_printf(const char *str, ...)
{
	va_list args;
	va_start(args, str);
	int count;
	
	count = 0;
	while (*str)
	{	
		if (*str == '%')
		{
			str++;
			if (*str == 'c')
				ft_putchar_fd((unsigned char)va_arg(args, int), 1);
			else if (*str == 's')
				ft_putstr_fd(va_arg(args, char*),1);
			else if (*str == 'd')
				ft_putnbr_fd(va_arg(args, int), 1);
			
		} 
		else
			ft_putchar_fd(*str, 1);
		str++;
	}
	va_end(args);
	return (0);
}

int main ()
{
	int nb = 12;

	ft_printf("test : %d\n", nb);
	printf("test : %d", nb);
}