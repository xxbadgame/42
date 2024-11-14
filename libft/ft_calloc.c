/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:41:44 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/14 15:27:24 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc( size_t nmemb, size_t size)
{
	unsigned char	*tab;

	tab = malloc(size * nmemb);
	if (!tab)
		return (NULL);
	ft_bzero(tab, (size * nmemb));
	return ((void *)tab);
}

/*
#include <stdio.h>          
#include <assert.h>
#define INT_NUMBER 10

int	main(void)
{
	
	int i;
	int *pointer = (int *) ft_calloc( INT_NUMBER, sizeof(int) );

	assert( pointer != NULL );

	for ( i=0; i<INT_NUMBER-1; i++ ) {
		pointer[i] = i;
	}


	for (i=0; i<INT_NUMBER; i++ ) {
		printf( "%d ", pointer[i] );
	}
	printf( "\n" );

	free( pointer );

	return 0;
}
*/