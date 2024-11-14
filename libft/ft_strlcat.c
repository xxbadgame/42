/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:29:07 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/14 16:19:36 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	len_dest;

	i = 0;
	len_dest = ft_strlen(dest);
	while (src[i] && i < (n - 1))
	{
		dest[len_dest + i] = src[i];
		i++;
	}
	dest[len_dest + i] = '\0';
	return (dest);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dest;

	len_dest = ft_strlen(dst);
	if (size <= len_dest)
		return (ft_strlen(src) + size);
	else
	{
		ft_strncat(dst, src, (size - len_dest));
		return (ft_strlen(src) + len_dest);
	}
	return (0);
}
