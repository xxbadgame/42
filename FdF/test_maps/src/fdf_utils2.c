/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:47:56 by yannis            #+#    #+#             */
/*   Updated: 2025/02/11 10:03:19 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	free_split(char **spl)
{
	int	i;

	i = 0;
	while (spl[i])
		free(spl[i++]);
	free(spl);
}

int	check_ext(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (str[len - 1] == 'f' || str[len - 2] == 'd' || str[len - 3] == 'f'
		|| str[len - 4] == '.')
		return (1);
	else
		return (0);
}
