/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:47:11 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/12/23 22:06:09 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_read_and_stock(t_list **lst, int fd)
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

static void	ft_check_overtaking(t_list *lst, char *overtaking)
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

static int	strlen_line_n(t_list *lst)
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

static char	*ft_result_line(t_list *lst, int j, int i)
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

#include <stdio.h>

int main()
{
	int fd;

	fd = open("test.txt", O_RDONLY);
	
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
}
