/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:47:11 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/26 17:11:02 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//#define BUFFER_SIZE 1

// creation noeud
t_list	*ft_lstnew(char *buff)
{
	t_list *node;
	
	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->buff = buff;
	node->next = NULL;
	return(node);
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

int		ft_lstsize(t_list *lst)
{
	int i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);	
}

void	ft_lstclear(t_list **lst)
{
	t_list *next;
	t_list *move;

	move = *lst;
	while (move != NULL)
	{
		free(move->buff);
		next = move->next;
		free(move);
		move = next;
	}
	*lst = NULL;
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	if (lst == NULL)
	{
		*lst = new;
		return ;
	}
	new->next = *lst;
	*lst = new;
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

// aficher la liste chaine
void	ft_print_linked_list(t_list **lst)
{
	t_list *move;

	move = *lst;
	while (move != NULL)
	{
		printf("%s -> ",move->buff);
		move = move->next;
	}
	printf("NULL\n");
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

// Sert a regarder a chaque fois dans toutes la liste chainee si il y a un \n
int		ft_check_in_line(t_list *lst)
{
	t_list *move;
	int i;
	
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

// Lire jusqu au \n en ajoutant des buff a la liste chaine
void	ft_read_and_stock(t_list **lst, int fd)
{
	int nb_bytes;
	char *buff;
	t_list *node;

	buff = NULL;
	while (ft_check_in_line(*lst) == 0)
	{
		buff = malloc(BUFFER_SIZE + 1);
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
		free(buff);
	}
}

char	*ft_check_overtaking(t_list *lst)
{
	int start;
	int i;
	int j;
	int size_over;
	char *str_over;

	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
		
	start = 0;
	i = 0;
	size_over = 0;
	while (lst->buff[i])
	{
		if (start == 1)
			size_over++;
		if (lst->buff[i] == '\n')
			start = 1;
		i++;
	}
	start = 0;
	i = 0;
	j = 0;
	str_over = malloc(size_over + 1);
	while (lst->buff[i])
	{
		if (start == 1)
			str_over[j++] = lst->buff[i];
		if (lst->buff[i] == '\n')
			start = 1;
		i++;
		
	}
	str_over[j] = 0;
	return (str_over);
}

char *ft_result_line(t_list *lst)
{
	int size_list;
	char *result;
	int i;
	int j;
	
	size_list = ft_lstsize(lst);
	result = malloc(size_list + 1);
	if (!result)
		return (result);
	i = 0;
	j = 0;
	while (lst)
	{
		i = 0;
		while (lst->buff[i])
		{
			result[j] = lst->buff[i];
			if (lst->buff[i] == '\n')
				return (result);
			j++;
			i++;
		}
		lst = lst->next;
	}
	result[j] = 0;
	return (result);
}

char *get_next_line(int fd)
{
	static t_list 		*lst;
	char 				*result_line;
	t_list 				*over_node;

	ft_read_and_stock(&lst, fd);
	ft_print_linked_list(&lst);
	result_line = ft_result_line(lst);
	over_node = ft_lstnew(ft_check_overtaking(lst));
	printf("visu over node : %s", over_node->buff);
	ft_lstclear(&lst);
	ft_lstadd_front(&lst, over_node);
	
	return(result_line);
}

int main()
{
	int fd;
	
	fd = open("text.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
}

/*
int main()
{
	int fd;
	char *str;
	
	fd = open("text.txt", O_RDONLY);
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		free(str);
	}
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	close(fd);
	fd = open("text.txt", O_RDONLY);
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
}
*/