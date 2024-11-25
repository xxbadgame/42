/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:14:16 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/25 16:05:17 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	convert_base_16(unsigned long long int nb, int maj)
{
	char	*base16;
	int		i;

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

int	ft_putptr(void *ptr)
{
	unsigned long long int	ptr_number;
	int						size;

	if (ptr == NULL)
	{
		ft_putstr("(nil)");
		return (5);
	}
	ptr_number = (unsigned long long int)ptr;
	size = 2;
	write(1, "0x", 2);
	size += convert_base_16(ptr_number, 0);
	return (size);
}

int	ft_arg_printf(const char *str, va_list args)
{
	int	count;

	count = 0;
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
	else if (*str == 'x')
		count += convert_base_16 ((unsigned int)va_arg(args, int), 0);
	else if (*str == 'X')
		count += convert_base_16 ((unsigned int)va_arg(args, int), 1);
	else if (*str == '%')
		count += ft_putchar('%');
	else
		return (-1);
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			count += ft_arg_printf(str, args);
		}
		else
			count += ft_putchar(*str);
		str++;
	}
	va_end(args);
	return (count);
}

/*
#include <stdlib.h>
#include <stdio.h>

int main ()
{
	printf("%d\n", ft_printf("yannis : fw %    d", 12));
	printf("%d", printf("vrai : fw %   d", "char" , 12));
}
*/