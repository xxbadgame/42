/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 22:13:23 by yannis            #+#    #+#             */
/*   Updated: 2025/01/03 14:38:14 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    execute_cmd(char *file, char *cmd)
{
    char *path_bin;
    char *full_path;
    char **detail_cmd;
    int len_opt;
    char **args;
    size_t dest_size ;

    len_opt = 0;
    detail_cmd = ft_split(cmd, ' ');
    
    while (detail_cmd[len_opt])
        len_opt++;
    
    path_bin = "/bin/";
    dest_size = ft_strlen(path_bin) + ft_strlen(detail_cmd[0]);
    full_path = malloc(dest_size + 1);
    ft_strlcpy(full_path, path_bin, ft_strlen(path_bin) + 1);
    ft_strlcat(full_path, detail_cmd[0], dest_size + 1);

    args = malloc(len_opt * sizeof(char *));
    int i_args = 0;

    // /bin/cmd[0]
    args[i_args++] = full_path;

    // suite du split commence à 1 et dans l'ordre execve on est a 1 aussi
    while (i_args < len_opt)
    {
        args[i_args] = detail_cmd[i_args];
        i_args++;
    }
    
    args[i_args++] = file;
    args[i_args++] = NULL;
    
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
