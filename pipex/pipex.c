/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 22:13:23 by yannis            #+#    #+#             */
/*   Updated: 2025/01/08 13:08:54 by ynzue-es         ###   ########.fr       */
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
    int heredoc;
    int i;
    int j;

    last_fd = -1;
    heredoc = 0;

    if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
        heredoc = 1;

    if (heredoc)
    {

        int fd, saved_stdout;
        char *line;

        fd = open("here_doc", O_RDWR | O_CREAT | O_TRUNC, 0644);
        
        saved_stdout = dup(STDOUT_FILENO);	
        dup2(fd, STDOUT_FILENO);

        
        
        line = get_next_line(STDIN_FILENO);
        while(line && ft_strncmp(ft_strtrim(line, "\n"), argv[2], ft_strlen(line)) != 0)
        {
            write(1, line, ft_strlen(line));
            line = get_next_line(STDIN_FILENO);
        }
        
        dup2(saved_stdout, STDOUT_FILENO);

        free(line);
        close(fd);
        close(saved_stdout);

        infile = open("here_doc", O_RDONLY);
        outfile = open(argv[argc - 1],  O_WRONLY | O_CREAT);
    }
    else
    {
        infile = open(argv[1], O_RDONLY);
        outfile = open(argv[argc - 1],  O_WRONLY | O_CREAT | O_TRUNC);
    }

    i = 0;
    if (heredoc)
        j = 3;
    else
        j = 2;
    while (argv[j + 1] != NULL)
    {
        if (argv[j + 2] != NULL) {
            if (pipe(fd) == -1) {
                perror("Pipe failed");
                exit(1);
            }
        }

        if (i == 0)
            pipex(infile, fd[1], cmds[i], envp);
        else if (argv[j + 2] == NULL)
            pipex(last_fd, outfile, cmds[i], envp);
        else
            pipex(last_fd, fd[1], cmds[i], envp);


        if (last_fd != -1) 
            close(last_fd);
        if (i < argc - 4) 
            close(fd[1]);
        
        last_fd = fd[0];
        
        j++;
        i++;
    }
}

int main(int argc, char **argv, char **envp)
{
    char ***cmds;
    int start;
    int i;

    if (argc <= 2)
        return 1;

    if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
        start = 3;
    else
        start = 2;
        
    i = start;
    cmds = malloc((argc + 1) * sizeof(char **));
    while (i < (argc - 1))
    {
        cmds[i-start] = ft_split(argv[i], ' ');
        i++;
    }
    cmds[i-2] = NULL;
    
    
    exec_cmds(argc, argv, cmds, envp);
    
    return 0;
}
