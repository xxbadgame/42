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

#define BUFFER_SIZE 3

// creation noeud
t_list	*ft_lstnew(char *buff)
{
	t_list *node;
	
	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->buff = buff;
	node->next = NULL;
}

// fonction ajouter dans la liste
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *move;

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

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	i;

	str = malloc(ft_strlen(s) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

// Checker dans le buffer si il y a un \n
int		ft_check_in_buff(char *buff)
{
	if (buff == NULL)
		return (0);
	while (*buff)
	{
		if (*buff == '\n')
			return (1);
		buff++;
	}
	return (0);
}

// Lire jusqu au \n en ajoutant des str a la liste chaine
void	ft_read_and_stock(t_list **lst, int fd)
{
	int nb_bytes;
	char *buff;
	t_list *node;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return ;
	nb_bytes = read(fd, buff, BUFFER_SIZE);
	if (nb_bytes == -1 || nb_bytes == 0)
	{
		free(buff);
		return ;
	}
	buff[nb_bytes] = '\0';
	while (ft_check_in_buff(buff) == 0)
	{
		nb_bytes = read(fd, buff, BUFFER_SIZE);
		if (nb_bytes == -1)
		{
			free(buff);
			return ;
		}
		if (nb_bytes == 0)
			break ;
		buff[nb_bytes] = '\0';
		node = ft_lstnew(ft_strdup(buff));
		if (!node)
		{
			free(buff);
			return ;
		}
		ft_lstadd_back(lst, node);
	}

	if (ft_check_in_buff(buff) || nb_bytes > 0)
	{
		node = ft_lstnew(ft_strdup(buff));
		if (node)
			ft_lstadd_back(lst, node);
	}

	free(buff);
}

// aficher la liste chaine
void	ft_print_linked_list(t_list **lst)
{
	t_list *move;

	move = *lst;
	while (move != NULL)
	{
		printf("%s ->",move->buff);
		move = move->next;
	}
	printf("NULL");
}

/*
char *get_next_line(int fd)
{
	
}
*/

int main()
{
	t_list 	*lst = NULL;
	int		fd;

	fd = open("text.txt", O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error", 5);
		return (1);
	}

	ft_read_and_stock(&lst, fd);
	ft_print_linked_list(&lst);
	close(fd);

	return (0);
}