/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:10:58 by yannis            #+#    #+#             */
/*   Updated: 2025/01/14 17:05:27 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (*s1++ && *s2++)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		i++;
	}
	return (*s1 - *s2);
}

int	find_str(char *arg, char *str)
{
	int	i;

	i = 0;
	while (arg[i] == str[i] && arg[i] && str[i])
	{
		if (arg[i + 1] == '\0' && str[i + 1] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int	duplicates_error(char **args, int split)
{
	int	i;
	int	y;

	if (split)
		i = 0;
	else
		i = 1;
	while (args[i])
	{
		y = 1 + i;
		while (args[y])
		{
			if (find_str(args[i], args[y]) == 1)
			{
				return (-1);
			}
			y++;
		}
		i++;
	}
	return (0);
}

int	real_number_checker(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '-' && ft_isdigit(str[i + 1]))
			i++;
		else if (ft_isdigit(str[i]) == 0)
			return (-1);
		else
			i++;
	}
	return (1);
}
