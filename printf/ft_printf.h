/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:24:17 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/18 18:02:21 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include <unistd.h>
#include <stdarg.h>

int	ft_printf(const char *str, ...);
int ft_putchar(char c);
int ft_putstr(char *str);
int ft_putnbr(int n);
int ft_putnbr_usigned(unsigned int n);
int convert_base_16(unsigned long long int nb, int maj);
int ft_putptr(void *ptr);
int ft_put_little_hex(int ptr);
int ft_put_big_hex(int ptr);

#endif