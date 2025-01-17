/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 22:13:23 by yannis            #+#    #+#             */
/*   Updated: 2025/01/17 17:39:36 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void close_fds(int in_fd, int out_fd)
{
    if (in_fd != -1) 
        close(in_fd);
    if (out_fd != -1) 
        close(out_fd);
}

int pipex_base(int in_fd, int out_fd, char **cmd, char **envp)
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
    close_fds(in_fd, out_fd);
    waitpid(pid, NULL, 0);
    return 0;
}

void heredoc_run(char **argv)
{
    int fd;
    char *line;
    char *trim_str;
    int saved_stdout;
    
    fd = open("here_doc", O_RDWR | O_CREAT | O_TRUNC, 0777);
    saved_stdout = dup(STDOUT_FILENO);	
    dup2(fd, STDOUT_FILENO);
    while(1)
    {
        line = get_next_line(STDIN_FILENO);
        trim_str = ft_strtrim(line, "\n");
        if (ft_strncmp(trim_str, argv[2], ft_strlen(line)) == 0)
            break;
        write(1, line, ft_strlen(line));
        free(line);
        free(trim_str);
    }
    dup2(saved_stdout, STDOUT_FILENO);
    free(line);
    free(trim_str);
    close(fd);
    close(saved_stdout);
}

void create_pipe(t_pipex *p_data, int *fd, int j)
{
    if (p_data->argv[j + 2] != NULL) {
        if (pipe(fd) == -1) {
            perror("Pipe failed");
            exit(1);
        }
    }
}

void run_cmds(t_pipex *p_data, char ***cmds, char **envp, int j)
{
    int last_fd;
    int fd[2];
    int i;
    
    last_fd = -1;
    i = 0;
    while (p_data->argv[++j + 1] != NULL)
    {
        create_pipe(p_data, fd, j);
        if (i == 0)
            pipex_base(p_data->infile, fd[1], cmds[i], envp);
        else if (p_data->argv[j + 2] == NULL)
            pipex_base(last_fd, p_data->outfile, cmds[i], envp);
        else
            pipex_base(last_fd, fd[1], cmds[i], envp);
        if (last_fd != -1) 
            close(last_fd);
        if (i++ < p_data->argc - 4)
            close(fd[1]);
        last_fd = fd[0];
    }
}

void exec_cmds(t_pipex *p_data, char ***cmds, char **envp)
{
    int heredoc;
    (void)envp;
    int j;

    heredoc = 0;
    if (ft_strncmp(p_data->argv[1], "here_doc", ft_strlen(p_data->argv[1])) == 0)
        heredoc = 1;
    if (heredoc)
    {
        heredoc_run(p_data->argv);
        p_data->infile = open("here_doc", O_RDONLY);
        p_data->outfile = open(p_data->argv[p_data->argc - 1],  O_WRONLY | O_CREAT | O_APPEND, 0777);
        j = 3;
    }
    else
    {
        p_data->infile = open(p_data->argv[1], O_RDONLY);
        p_data->outfile = open(p_data->argv[p_data->argc - 1],  O_WRONLY | O_CREAT | O_TRUNC, 0777);
        j = 2;
    }

    run_cmds(p_data, cmds, envp, j - 1);
}

int free_split(char **str_spl)
{
   int i;

   i = 0;
   while (str_spl[i])
        free(str_spl[i++]);
    return 0;
}

int free_cmds(int start, int argc, char ***cmds)
{
    int i;
    int y;
    
    i = start;
    y = 0;
    while (i < argc)
    {
        y = 0;
        while (cmds[i-start][y])
            free(cmds[i-start][y++]);
        free(cmds[i-start]);
        i++;
    }
    free(cmds);
    return 0;
}

int main(int argc, char **argv, char **envp)
{
    char ***cmds;
    int start;
    int i;
    t_pipex p_data;
    (void)envp;

    p_data.argc = argc;
    p_data.argv = argv;
    if (p_data.argc <= 2)
        return 1;
    if (ft_strncmp(p_data.argv[1], "here_doc", ft_strlen(p_data.argv[1])) == 0)
        start = 3;
    else
        start = 2;
    i = start - 1;
    cmds = malloc((p_data.argc + 1) * sizeof(char **));
    while (++i < p_data.argc)
        cmds[i-start] = ft_split(p_data.argv[i], ' ');
    cmds[i-start] = NULL;
    exec_cmds(&p_data, cmds, envp);
    free_cmds(start, argc, cmds);
    return 0;
}
