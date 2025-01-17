/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 22:50:30 by yannis            #+#    #+#             */
/*   Updated: 2025/01/17 15:33:33 by ynzue-es         ###   ########.fr       */
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

typedef struct s_pipex
{
    int infile;
    int outfile;
    int argc;
    char **argv;
} t_pipex;


char *ft_getenv(char *var_name, char *envp[]);
char *ft_path_to_cmd(char **cmd, char *envp[]);

#endif