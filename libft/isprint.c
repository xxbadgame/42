/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isprint.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:35:04 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/04 15:37:27 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int ft_isprint(int character)
{
    if (character >= 32 && character <= 126)
    {
        return 1;
    }
    return 0;
}