/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:59:47 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/11/06 11:34:05 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

int ft_memcmp(const void *s1, const void *s2, size_t n)
{
    const unsigned char *ptr_s1 = s1;
    const unsigned char *ptr_s2 = s2;

    while (n--)
    {
        if (*ptr_s1 != *ptr_s2)
        {
            return (*ptr_s1 - *ptr_s2);
        }
        ptr_s1++;
        ptr_s2++;
    }
    return (*ptr_s1 - *ptr_s2);
}


int main() {

    int array1 [] = { 54, 85, 20, 63, 21 };
    int array2 [] = { 54, 85, 19, 63, 21 };
    size_t size = sizeof( int ) * 5;

    assert( memcmp( array1, array2, size) == ft_memcmp( array1, array2, size) );       
    assert( memcmp( array1, array1, size) == ft_memcmp( array1, array1, size) );       
    assert( memcmp( array2, array1, size) == ft_memcmp( array2, array1, size) );       
    
    printf( "Test is ok\n" );
    
    return 0;
}