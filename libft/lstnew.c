/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstnew.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:31:53 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/08 11:38:18 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list *ft_lstnew(void *content)
{
    t_list *new;
    new = malloc(sizeof(t_list));
    new->content = content;
    new->next = NULL;

    return new;
}