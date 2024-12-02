/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:20:05 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/29 15:54:14 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (write(1, "(null)", 6));
	else
		return (write(1, str, ft_strlen(str)));
}

int	ft_putnbr(int n)
{
	unsigned int	nb;
	int				i;

	i = 0;
	if (n < 0)
	{
		ft_putchar('-');
		i++;
		nb = -n;
	}
	else
		nb = n;
	if (nb >= 10)
		i += ft_putnbr(nb / 10);
	ft_putchar(nb % 10 + '0');
	i++;
	return (i);
}

int	ft_putnbr_usigned(unsigned int n)
{
	int	i;

	i = 0;
	if (n >= 10)
		i += ft_putnbr(n / 10);
	ft_putchar(n % 10 + '0');
	i++;
	return (i);
}
