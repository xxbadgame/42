/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:14:16 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/22 14:14:28 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>


int convert_base_16(unsigned long long int nb, int maj)
{
	char *base16;
	int i;

	if (maj)
		base16 = "0123456789ABCDEF";
	else
		base16 = "0123456789abcdef";
	i = 0;
	
	if (nb >= 16)
		i += convert_base_16(nb / 16, maj);
	ft_putchar(base16[nb % 16]);
	i++;
	
	return (i);
}

int ft_putptr(void *ptr)
{
	int size;

	if (ptr == NULL)
	{
		ft_putstr("(nil)");
		return (5);
	}
	unsigned long long int ptr_number;
	ptr_number = (unsigned long long int)ptr;
	size = 2;
	write(1, "0x", 2);
	size += convert_base_16(ptr_number,0);
	return (size);
}

int ft_put_little_hex(int ptr)
{
	int size;
	
	size = 0;
	size += convert_base_16((unsigned int)ptr, 0);
	return (size);
}

int ft_put_big_hex(int ptr)
{
	int size;
	
	size = 0;
	size += convert_base_16((unsigned int)ptr, 1);
	return (size);
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
				count += ft_putstr(va_arg(args, char *));
			else if (*str == 'p')
				count += ft_putptr(va_arg(args, void *));
			else if (*str == 'd')
				count += ft_putnbr(va_arg(args, int));
			else if (*str == 'i')
				count += ft_putnbr(va_arg(args, int));
			else if (*str == 'u')
				count += ft_putnbr_usigned(va_arg(args, unsigned long long int));
			else if(*str == 'x')
				count += ft_put_little_hex(va_arg(args, int));
			else if(*str == 'X')
				count += ft_put_big_hex(va_arg(args, int));
			else if(*str == '%')
				count += ft_putchar('%');
			else
				return (-1);
		}
		else
			count += ft_putchar(*str);
		str++;
		
	}
	va_end(args);
	return (count);
}


#include <stdlib.h>

int main ()
{
	printf("%d", ft_printf("fw % wewe", 12));
	//printf("\nresult2 : %d", printf(" ewwe  % wewe", 12));
}
