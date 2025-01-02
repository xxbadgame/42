/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:09:26 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/15 12:01:01 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*move;
	t_list	*next;

	if (!lst || !del)
		return ;
	if (*lst == NULL)
		return ;
	move = *lst;
	while (move != NULL)
	{
		next = move->next;
		ft_lstdelone(move, *del);
		move = next;
	}
	*lst = NULL;
}
