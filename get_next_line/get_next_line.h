/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:23:04 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/26 17:11:35 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

# ifndef BUFFER_SIZE
#define BUFFER_SIZE 2
#endif

typedef struct s_list
{
	char			*buff;
	struct s_list	*next;
}	t_list;

char *get_next_line(int fd);

#endif