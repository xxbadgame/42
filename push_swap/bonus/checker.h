/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 08:20:18 by yannis            #+#    #+#             */
/*   Updated: 2025/01/15 15:42:03 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <stdio.h>
# include <string.h>

typedef struct s_stack
{
	int	*arr;
	int	top;
}		t_stack;

void	push_a(t_stack *stack_a, t_stack *stack_b);
void	push_b(t_stack *stack_a, t_stack *stack_b);
void	swap_a(t_stack *stack_a);
void	swap_b(t_stack *stack_b);
void	swap_all(t_stack *stack_a, t_stack *stack_b);
void	rotate_a(t_stack *stack_a);
void	rotate_b(t_stack *stack_b);
void	rotate_all(t_stack *stack_a, t_stack *stack_b);
void	reverse_rotate_a(t_stack *stack_a);
void	reverse_rotate_b(t_stack *stack_b);
void	reverse_rotate_all(t_stack *stack_a, t_stack *stack_b);
int		duplicates_error(char **args, int split);
int		real_number_checker(char *str);
int		len_stack_split(char **spl_str);
int		spl_stack(t_stack *stack_a, char **spl_str, int len_spl);
int		argc_stack(t_stack *stack_a, char **argv, int argc);
int		create_stack(int argc, char **argv, t_stack *stack_a, t_stack *stack_b);
void 	free_split(char **spl_str);

#endif