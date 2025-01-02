/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 22:13:23 by yannis            #+#    #+#             */
/*   Updated: 2025/01/02 00:56:02 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    execute_cmd(char *file, char *cmd)
{
    char *path_bin;
    char *full_path;
    char **detail_cmd;
    size_t dest_size ;

    detail_cmd = ft_split(cmd, ' ');

    path_bin = "/bin/";
    dest_size = ft_strlen(path_bin) + ft_strlen(detail_cmd[0]);
    full_path = malloc(dest_size + 1);
    ft_strlcpy(full_path, path_bin, ft_strlen(path_bin) + 1);
    ft_strlcat(full_path, detail_cmd[0], dest_size + 1);
    
    printf("file : %s", file);
    
    char *args[4];
    args[0] = full_path;
    // uniquement si on ajoute un argument
    args[1] = detail_cmd[1];
    args[2] = file;
    args[3] = NULL;
    
    if (execve(full_path, args, NULL) == -1) {
        perror("execve");
        exit(1);
    }
}

// execute une commande dans la console 
int main(int argc, char **argv)
{
    if (argc < 2)
    {
        perror("no args");
        exit(1);
    }
    execute_cmd(argv[1], argv[2]);
    return 0;
}
