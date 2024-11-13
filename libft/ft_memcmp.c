/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:59:47 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/13 16:33:05 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ptr_s1;
	const unsigned char	*ptr_s2;

	ptr_s1 = s1;
	ptr_s2 = s2;
	if (n == 0)
		return (0);
	n = n - 1;
	while (n--)
	{
		if (*ptr_s1 != *ptr_s2)
			return ((unsigned char)*ptr_s1 - (unsigned char)*ptr_s2);
		ptr_s1++;
		ptr_s2++;
	}
	return ((unsigned char)*ptr_s1 - (unsigned char)*ptr_s2);
}
