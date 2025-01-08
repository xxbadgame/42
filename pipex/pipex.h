/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 22:50:30 by yannis            #+#    #+#             */
/*   Updated: 2025/01/08 01:40:29 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "get_next_line/get_next_line.h"
#include "libft/libft.h"

char *ft_getenv(char *var_name, char *envp[]);
char *ft_path_to_cmd(char **cmd, char *envp[]);

#endif