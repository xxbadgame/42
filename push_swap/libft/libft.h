/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:37:37 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/01/14 17:15:05 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

long int			ft_atol(const char *str);
int					ft_isdigit(int digit);
char				**ft_split(char const *s, char c);
size_t				ft_strlen(const char *str);
char				*ft_strtrim(char const *s1, char const *set);

#endif