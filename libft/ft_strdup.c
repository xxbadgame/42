/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:52:57 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/13 16:53:41 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		size;
	char	*str;
	char	*ptr;

	size = ft_strlen(s);
	str = malloc(size + 1);
	ptr = str;
	while (*s)
	{
		*str++ = *s++;
	}
	*str = 0;
	return (ptr);
}
