/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:45:35 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/20 16:02:45 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*ptr_dest;
	const unsigned char	*ptr_src;

	ptr_dest = dest;
	ptr_src = src;
	if (ptr_src != ptr_dest)
	{
		if (ptr_src > ptr_dest)
		{
			while (n--)
				*ptr_dest++ = *ptr_src++;
		}
		else
		{
			while (n--)
				ptr_dest[n] = ptr_src[n];
		}
	}
	return (dest);
}
