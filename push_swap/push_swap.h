/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 14:22:28 by ynzue-es          #+#    #+#             */
/*   Updated: 2024/12/06 17:11:17 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "stdio.h"
# include "libft/libft.h"
#define MAX_SIZE 100

typedef struct s_stack 
{
	int arr[MAX_SIZE];
	int top;
} t_stack;

void push(t_stack *stack, int value);

#endif