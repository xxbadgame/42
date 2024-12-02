/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:31:31 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/14 16:44:50 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*ptr_src;
	unsigned char		*ptr_dest;

	if (dest == NULL && src == NULL)
		return (NULL);
	ptr_dest = dest;
	ptr_src = src;
	while (n--)
	{
		*ptr_dest++ = (unsigned char)*ptr_src++;
	}
	return (dest);
}
