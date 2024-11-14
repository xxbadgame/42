/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:38:21 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/14 15:37:54 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str;

	str = s;
	while (n--)
	{
		if (*str == (unsigned char)c)
			return ((void *)str);
		str++;
	}
	return (NULL);
}
/*
int main() {

	char data[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
	const unsigned int size = 10;

	
}
*/