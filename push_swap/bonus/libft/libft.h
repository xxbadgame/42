/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:37:37 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/01/14 16:48:18 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

long int	ft_atol(const char *str);
int			ft_isdigit(int digit);
char		**ft_split(char const *s, char c);
size_t		ft_strlen(const char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strtrim(char const *s1, char const *set);
int			ft_isdigit(int digit);

#endif