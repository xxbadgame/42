/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isalum.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:21:53 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/12 11:50:40 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int character)
{
	if (character >= 'A' && character <= 'Z'
		|| character >= 'a' && character <= 'z'
		|| character >= '0' && character <= '9')
	{
		return (1);
	}
	return (0);
}
