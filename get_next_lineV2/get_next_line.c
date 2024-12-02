/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:54:55 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/12/02 16:58:36 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "get_next_line.h"

int		ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char    *ft_strjoin(char const *s1, char const *s2)
{
        int             len_s1;
        int             len_s2;
        char    *strjoin;
        int             i;
        int             j;

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



char *get_next_line(int fd)
{
	char *line;
	int nb_bytes;
	static char buff[BUFFER_SIZE];
	int i_buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
		
	i_buff = 0;
	line = malloc(1);
	while ((nb_bytes = read(fd, buff, BUFFER_SIZE)) > 0)
	
		printf("%s", buff);
	}

	//printf("%s\n", line);
	return (NULL);
	// free strjoin
}

int main(void)
{
	int fd;
	char *line;
	char *line2;
	int i;

	line = "test";
	line2 = "hello";
	i = 0;
	
	fd = open("test.txt", O_RDONLY); 
	get_next_line(fd);
	
	return (0);
}