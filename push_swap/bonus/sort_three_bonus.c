/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 23:05:39 by yannis            #+#    #+#             */
/*   Updated: 2024/12/20 21:35:52 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../push_swap.h"

int sort_three(t_stack *stack_a)
{
    int ind_big;
    
    ind_big = find_max_ind(stack_a);

    if (ind_big == stack_a->top)
        rotate_a(stack_a);
    else if (ind_big == stack_a->top - 1)
        reverse_rotate_a(stack_a);
    if (stack_a->arr[stack_a->top] > stack_a->arr[stack_a->top - 1])
        swap_a(stack_a);
}