/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:52:57 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/20 16:04:07 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	char	*ptr;

	str = malloc(ft_strlen(s) + 1);
	if (!str)
		return (NULL);
	ptr = str;
	while (*s)
	{
		*str++ = *s++;
	}
	*str = 0;
	return (ptr);
}
