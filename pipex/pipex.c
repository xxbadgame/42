/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 22:13:23 by yannis            #+#    #+#             */
/*   Updated: 2025/01/07 19:38:08 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int pipex(int in_fd, int out_fd, char **cmd, char **envp)
{
    char    *full_path;
    int     pid;
    
    pid = fork();
    if (pid < 0)
        return 1;

    if (pid == 0) 
    {
        if (in_fd != -1) 
        {
            dup2(in_fd, STDIN_FILENO);
            close(in_fd);
        }

        if (out_fd != -1) 
        {
            dup2(out_fd, STDOUT_FILENO);
            close(out_fd);
        }
        
        full_path = ft_path_to_cmd(cmd, envp);
        execve(full_path, cmd, envp);
    }
    
    if (in_fd != -1) 
        close(in_fd);
    if (out_fd != -1) 
        close(out_fd);

    close(in_fd);
    close(out_fd);
    waitpid(pid, NULL, 0);
    
    return 0;
}

void exec_cmds(int argc, char **argv, char ***cmds, char **envp)
{
    int fd[2];
    int infile;
    int outfile;
    int last_fd;
    int i;

    last_fd = -1;
    infile = open(argv[1], O_RDONLY);
    outfile = open(argv[argc - 1],  O_WRONLY | O_CREAT | O_TRUNC);

    i = 1;
    while (i <= (argc - 2))
    {
        if (pipe(fd) == -1)
        {
            perror("Fork failed");
            exit(1);
        }

        if (i == 1)
            pipex(infile, fd[1], cmds[i], envp);
        else if (i == (argc - 1))
            pipex(last_fd, outfile, cmds[i], envp);
        else
            pipex(last_fd, fd[1], cmds[i], envp);

        if (last_fd != -1) 
            close(last_fd);
        close(fd[1]);
        last_fd = fd[0];
        
        i++;
    }
}


int main(int argc, char **argv, char **envp)
{
    char ***cmds;
    int i;

    if (argc != 5)
        return 1;

    i = 2;
    cmds = malloc((argc + 1) * sizeof(char **));
    while (i < (argc - 1))
    {
        cmds[i-2] = ft_split(argv[i], ' ');
        i++;
    }
    cmds[i-2] = NULL;
    exec_cmds(argc, argv, cmds, envp);
    
    return 0;
}
