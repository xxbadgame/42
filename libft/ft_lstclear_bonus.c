/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:09:26 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/14 15:31:13 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*move;

	if (!lst || !del)
		return ;
	if (*lst == NULL)
	{
		return ;
	}
	move = *lst;
	while (move != NULL)
	{
		ft_lstdelone(move, *del);
		move = move->next;
	}
	*lst = NULL;
}
