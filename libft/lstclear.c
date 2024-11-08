/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstclear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:09:26 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/08 15:40:05 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void ft_lstdelone(t_list *lst, void (*del)(void *))
{ 
    del((void *)lst);
    free(lst);
}

void ft_lstclear(t_list **lst, void (*del)(void *))
{
    t_list *move;
    
    move = *lst;
    
    while (move->next != NULL)
    {
        ft_lstdelone(move, *del);
    }
}