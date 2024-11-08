/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:25:19 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/06 18:36:47 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int ft_count_word(char const *s, char sep)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (s[i])
    {
        if (s[i] != sep && s[i + 1] == sep || s[i] != sep && s[i + 1] == '\0')
            count++;
        i++;
    }
    return count;
}

int ft_len_words(char const *s, char sep)
{
    int i;

    i = 0;
    while (s[i] != sep)
        i++;
    return i;
}

char *allocate_copy(char const *str, char sep)
{
    int i;
    char *copy_word;

    i = 0;
    copy_word = malloc(ft_len_words(str, sep) + 1);
    if (!copy_word)
        return NULL;
        
    while (str[i] != sep)
    {
        copy_word[i] = str[i];
        i++;
    }
    copy_word[i] = '\0';
    return copy_word;
}


char **ft_split(char const *s, char c)
{
    int nb_words;
    char **split;
    int i;
    int j;
    
    i = 0;
    j = 0;
    nb_words = ft_count_word(s, c);
    split = malloc((nb_words + 1) * sizeof(char *));
    if (!split)
        return NULL;
    
    while (i < nb_words)
    {
        while (*s == c)
            s++;
        split[i] = allocate_copy(s, c);
        while (*s != c)
            s++;
        i++;
        
    }
    return split;
}


int main()
{
    char *str = "     testerg2ge22rrew2ge2rgegp";
    char sep = '2';
    int i;

    i = 0;
    char **split;
    split = ft_split(str, sep);

    while (split[i])
    {
        printf("%s\n", split[i]);
        i++;
    }
    
    
}

