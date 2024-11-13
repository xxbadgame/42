/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:32:13 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/13 19:00:22 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	size_number(int n)
{
	unsigned int	nb;
	int				count;

	nb = n;
	count = 0;
	if (n < 0)
		nb = -n;
	while (nb >= 10)
	{
		nb /= 10;
		count++;
	}
	count++;
	return (count);
}

char	*allocate_number(int n)
{
	int		size;
	char	*nb_str;

	size = size_number(n);
	if (n >= 0)
	{
		nb_str = malloc(size + 1);
	}
	else
	{
		nb_str = malloc(size + 2);
	}
	return (nb_str);
}


char	*ft_itoa(int n)
{
	int				size;
	int				i;
	char			*nb_str;
	unsigned int	nb;

	nb = (-(n) * (n < 0) + (n) * ((n) >= 0));
	size = size_number(n) + (n < 0);

	nb_str = allocate_number(n);
	if (!nb_str)
		return (NULL);

	i = 0;
	while (i < size_number(n))
	{
		nb_str[size - i - 1] = (nb % 10) + '0';
		nb /= 10;
		i++;
	}
	if (n < 0)
		nb_str[0] = '-';

	nb_str[size] = '\0';

	return (nb_str);
}