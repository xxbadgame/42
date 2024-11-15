/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:14:16 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/15 17:56:50 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "../libft/libft.h"
#include <stdio.h>

int ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
		ft_putchar(str[i]);
	return (i);
}

int ft_putnbr(int n)
{
	int i;
	int size;
	unsigned int nb;

	i = 0;
	nb = n;
	
	if (n < 0)
	{
		nb = -n;
	}
	while (i )
	{
		
	}
	
}

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
				count += ft_putchar((unsigned char)va_arg(args, int));
			else if (*str == 's')
				count += ft_putstr(va_arg(args, char*));
			else if (*str == 'd')
				ft_putnbr_fd(va_arg(args, int), 1);
			
		} 
		else
			ft_putchar_fd(*str, 1);
		str++;
		count++;
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