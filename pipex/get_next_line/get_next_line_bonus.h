/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:33:59 by yannis            #+#    #+#             */
/*   Updated: 2024/12/05 12:23:38 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

# ifndef FD_MAX
#  define FD_MAX 1024
# endif

typedef struct s_list
{
	char			buff[BUFFER_SIZE];
	struct s_list	*next;
}					t_list;

int					ft_strlen(const char *str);
t_list				*ft_lstnew(char *buff);
void				ft_lstadd_back(t_list **lst, t_list *new);
char				*ft_lstclear(t_list **lst);
int					ft_check_in_line(t_list *lst);
char				*get_next_line(int fd);

#endif