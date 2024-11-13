/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:40:41 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/13 16:40:23 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int	i;
	int	j;
	int base_len;

	i = 0;
	j = 0;
	base_len = len;

	if (*little == '\0')
		return ((char *)big);
	while (len--)
	{
		j = 0;
		while (little[j] == big[i + j] && i + j <= base_len)
		{
			if (little[j + 1] == '\0')
				return ((char *)big + i);
			j++;
		}
		i++;
	}
	return (NULL);
}

/*
int main()
{
	char *big = "lorem ipsum dolor sit amet";
	char *little = "dolor";
	size_t len = 15;

	printf("%s",ft_strnstr(big, little, len));
}
*/