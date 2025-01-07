/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 22:13:23 by yannis            #+#    #+#             */
/*   Updated: 2025/01/07 18:07:35 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"



int pipex(int infile, int outfile, char ***cmds, char **envp)
{
    char    *full_path;
    //int i;
    int fd[2];

    //i = 0;    
    if (pipe(fd) == -1) {
        return 1;
    }
    /*
    while (cmds[i] != NULL)
    {
        int pid1 = fork();
        if (pid1 < 0){
            return 2;
        }

        if (pid1 == 0) {
            dup2(infile, STDIN_FILENO);
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
            full_path = ft_path_to_cmd(cmds[0], envp);
            execve(full_path, cmds[0], envp);
        }

        int pid2 = fork();
        if (pid2 < 0) {
            return 3;
        }
        if (pid2 == 0) {        
            dup2(outfile, STDOUT_FILENO);
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            close(fd[1]);
            full_path = ft_path_to_cmd(cmds[1], envp);
            execve(full_path, cmds[1], envp);

        }
        close(fd[1]);
        close(fd[0]);
        waitpid(pid1, NULL, 0);
        waitpid(pid2, NULL, 0);
        i++;
    }
    */    

    int pid1 = fork();
    if (pid1 < 0){
        return 2;
    }

    if (pid1 == 0) {
        dup2(infile, STDIN_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        full_path = ft_path_to_cmd(cmds[0], envp);
        execve(full_path, cmds[0], envp);
    }

    int pid2 = fork();
    if (pid2 < 0) {
        return 3;
    }
    if (pid2 == 0) {        
        dup2(outfile, STDOUT_FILENO);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        full_path = ft_path_to_cmd(cmds[1], envp);
        execve(full_path, cmds[1], envp);

    }
    close(fd[1]);
    close(fd[0]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    
    return 0;
}

int main(int argc, char **argv, char **envp)
{
    char ***cmds;
    int i;
 
    if (argc < 2)
    {
        perror("no args");
        exit(1);
    }
    
    int infile = open(argv[1], O_RDONLY);

    i = 2;
    cmds = malloc((argc + 1) * sizeof(char **));
    while (i < (argc - 1))
    {
        cmds[i-2] = ft_split(argv[i], ' ');
        i++;
    }
    cmds[i-2] = NULL;

    int outfile = open(argv[i],  O_WRONLY | O_CREAT | O_TRUNC);

    pipex(infile, outfile, cmds, envp);
    
    return 0;
}
