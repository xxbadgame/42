/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 22:13:23 by yannis            #+#    #+#             */
/*   Updated: 2025/01/20 18:33:54 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex_base(int in_fd, int out_fd, char **cmd, char **envp)
{
	char	*full_path;
	int		pid;

	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
	{
		if (in_fd != -1)
			if (dup2(in_fd, STDIN_FILENO) == -1)
				return (-1);
		if (out_fd != -1)
			if (dup2(out_fd, STDOUT_FILENO) == -1)
				return (-1);
		close_fds(in_fd, out_fd);
		full_path = ft_path_to_cmd(cmd, envp);
		if (full_path == NULL)
			return (ft_putendl_fd("Command not found", 2), -1);
		if (execve(full_path, cmd, envp) == -1)
			return (ft_putendl_fd("Command not found", 2), -1);
	}
	close_fds(in_fd, out_fd);
	waitpid(pid, NULL, 0);
	return (0);
}

int	heredoc_run(char **argv)
{
	int		pipe_fd[2];
	char	*line;
	char	*trim_str;

	if (pipe(pipe_fd) < 0)
		return (-1);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		trim_str = ft_strtrim(line, "\n");
		if (ft_strncmp(trim_str, argv[2], ft_strlen(argv[2])) == 0)
		{
			free(line);
			free(trim_str);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
		free(trim_str);
	}
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO))
		return (-1);
	return (close(pipe_fd[0]));
}

int	exec_cmds(t_pipex *p_data, char ***cmds, char **envp)
{
	int	heredoc;

	heredoc = 0;
	if (ft_strncmp(p_data->argv[1], "here_doc", ft_strlen(p_data->argv[1])) == 0
		&& ft_strlen(p_data->argv[1]) == 8)
		heredoc = 1;
	if (heredoc)
	{
		if (heredoc_fds(p_data, cmds, envp) == -1)
			return (-1);
	}
	else
	{
		if (access(p_data->argv[1], F_OK) == 0)
		{
			if (no_heredoc_fds(p_data, cmds, envp) == -1)
				return (-1);
		}
		else
			ft_putendl_fd("File not found", 2);
	}
	return (0);
}

int	check_start_args(int argc, char **argv)
{
	int	start;

	if ((argc < 5) 
	|| ((argc < 6) 
	&& (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0)
			&& (ft_strlen("here_doc") == ft_strlen(argv[1]))))
	{
		ft_putendl_fd("Format error", 2);
		exit(1);
	}
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
		start = 3;
	else
		start = 2;
	return (start);
}

int	main(int argc, char **argv, char **envp)
{
	char	***cmds;
	int		i;
	int		start;
	t_pipex	p_data;

	p_data.argc = argc;
	p_data.argv = argv;
	start = check_start_args(p_data.argc, p_data.argv);
	i = start - 1;
	cmds = malloc((p_data.argc + 1) * sizeof(char **));
	if (!cmds)
		return (-1);
	while (++i < p_data.argc)
		cmds[i - start] = ft_split(p_data.argv[i], ' ');
	cmds[i - start] = NULL;
	exec_cmds(&p_data, cmds, envp);
	free_cmds(start, argc, cmds);
	return (0);
}
