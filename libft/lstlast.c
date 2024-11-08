/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstlast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:56:58 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/08 12:07:55 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list *ft_lstlast(t_list *lst)
{
    while (lst->next != NULL)
    {
        lst = lst->next;
    }
    return lst;
}