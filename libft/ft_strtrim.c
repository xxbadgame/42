/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:48:42 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/13 17:03:56 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_charset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	start_index(char const *str, char const *set)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(str);
	while (is_charset(str[i], set) && i < size)
		i++;
	return (i);
}

int	end_index(char const *str, char const *set)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (is_charset(str[i], set) && i >= 0)
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		i;
	char	*copy_s1;

	i = 0;
	start = start_index(s1, set);
	end = end_index(s1, set);

	if (start > end)
	{
		copy_s1 = malloc(1);
		copy_s1[i] = '\0';
		if (!copy_s1)
			return (NULL);

	}
	else
	{
		copy_s1 = malloc((end - start) + 2);
		if (!copy_s1)
			return (NULL);
		while (start <= end)
		{
			copy_s1[i] = s1[start];
			i++;
			start++;
		}
		copy_s1[i] = '\0';
	}
	return (copy_s1);
}

/*
int main()
{
	char *str = "lorem \n ipsum \t dolor \n sit \t amet";
	char *set = " ";

	printf("\nresult : \n%s",ft_strtrim(str, set));
}
*/
