/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:47:11 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/25 16:17:52 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#define BUFFER_SIZE 1

// creation d un noeud

t_list *ft_lstnew(void *content)
{
	t_list *node;
	
	node->content = content;
	node->next = NULL;
}

// fonction ajouter dans la liste

// Lire jusqu au \n en ajoutant des str a la liste chaine

// aficher la liste chaine

char *get_next_line(int fd)
{
	
}