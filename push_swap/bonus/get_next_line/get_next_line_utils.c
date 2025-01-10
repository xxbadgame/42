/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:24:17 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/01/10 01:16:11 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstnew(char *buff)
{
	t_list	*node;
	int		i;

	i = -1;
	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	while (buff[++i])
		node->buff[i] = buff[i];
	node->buff[i] = 0;
	node->next = NULL;
	return (node);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*move;

	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	move = *lst;
	while (move->next != NULL)
		move = move->next;
	move->next = new;
}

char	*ft_lstclear(t_list **lst)
{
	t_list	*next;
	t_list	*move;

	if (!lst || !*lst)
		return (NULL);
	move = *lst;
	while (move != NULL)
	{
		next = move->next;
		free(move);
		move = next;
	}
	*lst = NULL;
	return (NULL);
}

int	ft_check_in_line(t_list *lst)
{
	t_list	*move;
	int		i;

	move = lst;
	if (lst == NULL)
		return (0);
	while (move)
	{
		i = 0;
		while (move->buff[i])
		{
			if (move->buff[i] == '\n')
				return (1);
			i++;
		}
		move = move->next;
	}
	return (0);
}
