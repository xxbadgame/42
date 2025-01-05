/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 22:13:23 by yannis            #+#    #+#             */
/*   Updated: 2025/01/05 19:42:44 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

const void   *execute_cmd(char *file, char *cmd)
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

// vérifier les accès aux fichiers avec access

// supprimer les fichier si plus besoin

// voir la vidéo sur les dup et dup2

void    pipes_and_fork(file1, cmd1, cmd2, file2)
{
    int fd[2];
    int pid1;
    int pid2;

    if (pipe(fd) == -1){
        perror("An Error occured with opening the pipe\n");
    }
    
    pid1 = fork();
    printf("pid1 : %d\n", pid1);
    if (pid1 == 0) 
    {

        // faire le premier travail, partie gauche de la fonction
        
        write(dup2(fd[1], fd[0]) , execute_cmd(file1, cmd1), sizeof(void *));

    } 
    else 
    {
        // on crée le deuxieme enfant
        pid2 = fork();
        if (pid2 == 0)
        {
            void *result_left;
            // faire le deuxième travail, la partie droite de la fonction
            read(fd[0], result_left, sizeof(void *));
            execute_cmd(file2, cmd2);
        }
        else
            printf("Je suis le parent, PID = %d\n", getpid());
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

    pipes_and_fork(argv[1], argv[2], argv[3], argv[4]);

    return 0;
}
