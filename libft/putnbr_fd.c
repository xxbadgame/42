/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbr_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:35:34 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/08 10:18:52 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

void ft_putchar_fd(char c, int fd)
{
    write(fd, &c, 1);
}

void ft_putnbr_fd(int n, int fd)
{
    unsigned int nb;

    nb = n;
    if (n < 0)
    {
        ft_putchar_fd('-', fd);
        nb *= -1;  
    } 
    if (nb >= 10) {
        ft_putnbr_fd(nb / 10, fd);
    }
    ft_putchar_fd(nb % 10 + '0', fd);
}

int main()
{
    int i;

    i = 42;
    
    int fd = open("test.txt", O_RDWR | O_CREAT);
    ft_putnbr_fd(i, fd);
    return 0;
}