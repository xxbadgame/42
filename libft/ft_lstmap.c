/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:52:29 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/08 16:02:53 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"



t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
    t_list *result;
    t_list *move;

    move = lst;
    
    while (move->next != NULL)
    {
        move = move->next;
        f((void *)move->content);
        result = move->next;
    }
    
}
