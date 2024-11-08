/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstiter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:42:02 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/08 15:48:03 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void ft_lstiter(t_list *lst, void (*f)(void *))
{
    t_list *move;

    move = lst;

    while (move->next != NULL)
    {
        f((void *)move->content);
        move = move->next;
    }
}