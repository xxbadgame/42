/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:47:11 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/28 17:50:45 by ynzue-es         ###   ########.fr       */
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
	t_list	*node;

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
		free(move->buff);
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

void	ft_read_and_stock(t_list **lst, int fd)
{
	int		nb_bytes;
	char	*buff;
	t_list	*node;

	buff = NULL;
	while (ft_check_in_line(*lst) == 0)
	{
		buff = malloc(BUFFER_SIZE + 1);
		if (!buff)
			return ((void)ft_lstclear(lst));
		nb_bytes = read(fd, buff, BUFFER_SIZE);
		if (nb_bytes == -1)
			return (free(buff), (void)ft_lstclear(lst));
		if (nb_bytes == 0)
			return (free(buff));
		buff[nb_bytes] = '\0';
		node = ft_lstnew(buff);
		if (!node)
			return (free(buff), (void)ft_lstclear(lst));
		ft_lstadd_back(lst, node);
		free(buff);
	}
}

void	ft_check_overtaking(t_list *lst, char *overtaking)
{
	int	start;
	int	i;
	int	j;

	if (lst == NULL)
		return ;
	while (lst->next != NULL)
		lst = lst->next;
	start = 0;
	i = 0;
	j = 0;
	while (lst->buff[i])
	{
		if (start == 1)
			overtaking[j++] = lst->buff[i];
		if (lst->buff[i] == '\n')
			start = 1;
		i++;
	}
	overtaking[j] = 0;
}

int	strlen_line_n(t_list *lst)
{
	t_list	*move_size;
	int		size_list;
	int		i;

	move_size = lst;
	size_list = 0;
	i = 0;
	while (move_size)
	{
		i = 0;
		while (move_size->buff[i])
		{
			if (move_size->buff[i] == '\n')
			{
				size_list++;
				break ;
			}
			size_list++;
			i++;
		}
		move_size = move_size->next;
	}
	return (size_list);
}

char	*ft_result_line(t_list *lst, int j, int i)
{
	char	*result;

	result = malloc(strlen_line_n(lst) + 1);
	if (!result)
		return (NULL);
	while (lst)
	{
		i = -1;
		while (lst->buff[++i])
		{
			result[j] = lst->buff[i];
			if (lst->buff[i] == '\n')
			{
				result[j + 1] = '\0';
				return (result);
			}
			j++;
		}
		lst = lst->next;
	}
	result[j] = '\0';
	if (j == 0)
		return (free(result), NULL);
	return (result);
}

char	*get_next_line(int fd)
{
	t_list		*lst;
	char		*result_line;
	t_list		*over_node;
	static char	over_buff[BUFFER_SIZE + 1];

	lst = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	result_line = NULL;
	over_node = ft_lstnew(over_buff);
	if (!over_node)
		return (free(result_line), (char *)ft_lstclear(&lst));
	lst = over_node;
	ft_read_and_stock(&lst, fd);
	if (!lst)
		return (over_buff[0] = '\0', NULL);
	result_line = ft_result_line(lst, 0, 0);
	if (!result_line)
		return ((char *)ft_lstclear(&lst));
	ft_check_overtaking(lst, over_buff);
	ft_lstclear(&lst);
	if (ft_strlen(result_line) == 0)
		return (free(result_line), NULL);
	return (result_line);
}
