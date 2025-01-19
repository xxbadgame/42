/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 09:56:32 by yannis            #+#    #+#             */
/*   Updated: 2025/01/19 17:19:04 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	create_pipe(t_pipex *p_data, t_cmd *cmd)
{
	if (p_data->argv[cmd->j + 2] != NULL)
	{
		if (pipe(cmd->fd) == -1)
		{
			perror("Pipe failed");
			return (-1);
		}
	}
	return (0);
}

void	close_fds(int in_fd, int out_fd)
{
	if (in_fd != -1)
		close(in_fd);
	if (out_fd != -1)
		close(out_fd);
	return ;
}

int	heredoc_fds(t_pipex *p_data, char ***cmds, char **envp)
{
	int	stdin_backup;

	stdin_backup = dup(STDIN_FILENO);
	heredoc_run(p_data->argv);
	p_data->infile = dup(STDIN_FILENO);
	p_data->outfile = open(p_data->argv[p_data->argc - 1],
			O_WRONLY | O_CREAT | O_APPEND, 0777);
	dup2(stdin_backup, STDIN_FILENO);
	close(stdin_backup);
	if (run_cmds(p_data, cmds, envp, 2) == -1)
	{
		close_fds(p_data->infile, p_data->outfile);
		return (-1);
	}
	close_fds(p_data->infile, p_data->outfile);
	return (0);
}

int	no_heredoc_fds(t_pipex *p_data, char ***cmds, char **envp)
{
	p_data->infile = open(p_data->argv[1], O_RDONLY);
	p_data->outfile = open(p_data->argv[p_data->argc - 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (run_cmds(p_data, cmds, envp, 1) == -1)
	{
		close_fds(p_data->infile, p_data->outfile);
		return (-1);
	}
	close_fds(p_data->infile, p_data->outfile);
	return (0);
}
