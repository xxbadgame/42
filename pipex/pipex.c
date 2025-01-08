/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 22:13:23 by yannis            #+#    #+#             */
/*   Updated: 2025/01/08 02:25:28 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// micro terminal ici pour faire les pipes 1 à 1 avec a la fois le in et le out de la sortie standard
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

    waitpid(pid, NULL, 0);
    
    return 0;
}

// boucle de création de pipe
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

    i = 0;
    while (i < (argc - 3))
    {
        if (i < argc - 4) {
            if (pipe(fd) == -1) {
                perror("Pipe failed");
                exit(1);
            }
        }

        if (i == 0)
            pipex(infile, fd[1], cmds[i], envp);
        else if (i == (argc - 4))
            pipex(last_fd, outfile, cmds[i], envp);
        else
            pipex(last_fd, fd[1], cmds[i], envp);

        if (last_fd != -1) close(last_fd);
        if (i < argc - 4) close(fd[1]);
        
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

    if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
    {
        printf("test");
        get_next_line(1);

        /*
            int fd, saved_stdout;
            char *line;

            fd = open("file_temp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
            
            saved_stdout = dup(STDOUT_FILENO);	
            dup2(fd, STDOUT_FILENO);
            
            line = get_next_line(STDIN_FILENO);
            printf("%s\n", line);
            fflush(stdout); 
            
            dup2(saved_stdout, STDOUT_FILENO);
            
            free(line);
            close(fd);
            close(saved_stdout);

            return 0;
        */
    }
    
    exec_cmds(argc, argv, cmds, envp);
    return 0;
}
