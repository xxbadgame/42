/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstadd_back.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:59:51 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/08 16:11:10 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void ft_lstadd_back(t_list **lst, t_list *new)
{
    t_list *move;

    move = *lst;
    
    while (move->next != NULL)
    {
        move = new->next;
    }
    move->next = new;
}