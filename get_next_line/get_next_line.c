/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:47:11 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/20 14:32:24 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 1

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return i;
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		len_s1;
	int		len_s2;
	char	*strjoin;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	strjoin = malloc(len_s1 + len_s2 + 1);
	if (!strjoin)
		return (NULL);
	while (s1[i])
	{
		strjoin[i] = s1[i];
		i++;
	}
	while (s2[j])
		strjoin[i++] = s2[j++];
	strjoin[i] = '\0';
	return (strjoin);
}

char *read_file(int fd)
{
	char buffer[BUFFER_SIZE];
	char *buffer_memory;
	int i;
	int bytes_read;

	i = 0;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	buffer_memory = malloc(bytes_read);
	if(fd == -1){
        printf("\nError Opening File!!\n");
        exit(1);
    }

	while (i < bytes_read)
	{
		buffer_memory[i] = buffer[i];
		i++;
	}
	
	return (buffer_memory);
}

char *get_next_line(int fd)
{
	
}


int main()
{
	
	char* fileName = "text.txt";
	int fd = open(fileName, O_RDWR);

	printf("%s",get_next_line(fd));
}
