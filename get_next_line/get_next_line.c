/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:47:11 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/27 16:34:09 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//#define BUFFER_SIZE 1

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	i;

	if (!s)
    	return (NULL);
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

t_list	*ft_lstnew(char *buff)
{
	t_list *node;
	
	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->buff = ft_strdup(buff);
	if (!node->buff)
	{
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return(node);
}


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

void	ft_lstclear(t_list **lst)
{
	t_list *next;
	t_list *move;

	if (!lst || !*lst)
    	return;
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

// Potentielement inutile
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

void	ft_read_and_stock(t_list **lst, int fd)
{
	int nb_bytes;
	char *buff;
	t_list *node;

	buff = NULL;
	while (ft_check_in_line(*lst) == 0)
	{
		buff = malloc(BUFFER_SIZE + 1);
		if (!buff)
		{
			ft_lstclear(lst);
			return ;
		}
		nb_bytes = read(fd, buff, BUFFER_SIZE);
		if (nb_bytes == -1)
		{
			free(buff);
			ft_lstclear(lst);
			return ;
		}
		if (nb_bytes == 0)
		{
			free(buff);
			break;
		}
		buff[nb_bytes] = '\0';
		node = ft_lstnew(buff);
		if (!node)
		{
			free(buff);
			ft_lstclear(lst);
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
	if (size_over == 0)
    	return (NULL);
	start = 0;
	i = 0;
	j = 0;
	str_over = malloc(size_over + 1);
	if (!str_over)
		return (NULL);
	while (lst->buff[i])
	{
		if (start == 1)
			str_over[j++] = lst->buff[i];
		if (lst->buff[i] == '\n')
			start = 1;
		i++;
		
	}
	if (str_over[0] == 0)
	{
		free(str_over);
    	return (NULL);
	}
	str_over[j] = 0;
	return (str_over);
}

char *ft_result_line(t_list *lst)
{
	int size_list;
	t_list *move_size;
	char *result;
	int i;
	int j;
	int testI;
	
	size_list = 0;
	move_size = lst;
	testI = 0;
	while (move_size)
	{
		testI = 0;
		while (move_size->buff[testI])
		{
			if (move_size->buff[testI] == '\n')
			{
				size_list++;
				break;
			}
			size_list++;
			testI++;
		}
		move_size = move_size->next;
	}
	result = malloc(size_list + 1);
	if (!result)
		return (NULL);
	j = 0;
	while (lst)
	{
		i = 0;
		while (lst->buff[i])
		{
			result[j] = lst->buff[i];
			if (lst->buff[i] == '\n')
			{
				result[j + 1] = '\0';
				return (result);
			}
			j++;
			i++;
		}
		lst = lst->next;
	}
	result[j] = '\0';
	if (j == 0)
    {
        free(result);
        return (NULL);
    }
	return (result);
}


char *get_next_line(int fd)
{
	static t_list 		*lst;
	char 				*result_line;
	t_list 				*over_node;
	char				*over_buff;

	ft_read_and_stock(&lst, fd);
	if (!lst)
		return (NULL);
	result_line = ft_result_line(lst);
	if (!result_line)
	{
		ft_lstclear(&lst);
		return (NULL);
	}
	over_buff = ft_check_overtaking(lst);
	if (!over_buff)
	{
		ft_lstclear(&lst);
		return (result_line);
	}
	over_node = ft_lstnew(over_buff);
	if (!over_node)
		{
			free(result_line);
			free(over_buff);
			ft_lstclear(&lst);
			return (NULL);
		}
	ft_lstclear(&lst);
	// lst = NULL dircetement 
	ft_lstadd_front(&lst, over_node);
	
	if (ft_strlen(result_line) == 0)
	{
		free(result_line);
		return (NULL);
	}
	free(over_buff);
	return (result_line);
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