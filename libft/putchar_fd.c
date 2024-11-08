/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putchar_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 09:04:43 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/08 09:36:37 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

void ft_putchar_fd(char c, int fd)
{
    write(fd, &c, 1);
}

int main()
{
    int fd = open("test.txt", O_RDWR | O_CREAT);
    ft_putchar_fd('d', fd);
}