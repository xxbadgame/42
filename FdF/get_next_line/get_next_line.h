/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:23:04 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/12/02 01:10:42 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

typedef struct s_list
{
	char			buff[BUFFER_SIZE];
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(char *buff);
void				ft_lstadd_back(t_list **lst, t_list *new);
char				*ft_lstclear(t_list **lst);
int					ft_check_in_line(t_list *lst);
void				ft_read_and_stock(t_list **lst, int fd);
void				ft_check_overtaking(t_list *lst, char *overtaking);
int					strlen_line_n(t_list *lst);
char				*ft_result_line(t_list *lst, int j, int i);
char				*get_next_line(int fd);

#endif