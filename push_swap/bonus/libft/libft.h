/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:37:37 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/01/10 01:18:58 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>


int		ft_atoi(const char *str);
int		ft_isdigit(int digit);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *str);
char	*ft_strtrim(char const *s1, char const *set);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);

#endif