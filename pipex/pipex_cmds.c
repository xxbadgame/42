/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:46:12 by yannis            #+#    #+#             */
/*   Updated: 2025/01/19 17:46:15 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	run_cmd(t_pipex *p_data, t_cmd *cmd, char ***cmds, char **envp)
{
	if (cmd->i == 0)
	{
		if (pipex_base(p_data->infile, cmd->fd[1], cmds[cmd->i], envp) == -1)
			return (close(cmd->fd[1]), -1);
	}
	else if (p_data->argv[cmd->j + 2] == NULL)
	{
		if (pipex_base(cmd->last_fd, p_data->outfile, cmds[cmd->i], envp) == -1)
			return (close(cmd->last_fd), -1);
	}
	else
	{
		if (pipex_base(cmd->last_fd, cmd->fd[1], cmds[cmd->i], envp) == -1)
			return (close(cmd->last_fd), close(cmd->fd[1]), -1);
	}
	return (0);
}

int	run_cmds(t_pipex *p_data, char ***cmds, char **envp, int j)
{
	t_cmd	cmd;

	cmd.last_fd = -1;
	cmd.i = 0;
	cmd.j = j;
	while (p_data->argv[++cmd.j + 1] != NULL)
	{
		create_pipe(p_data, &cmd);
		if (run_cmd(p_data, &cmd, cmds, envp) == -1)
			return (-1);
		if (cmd.last_fd != -1)
			close(cmd.last_fd);
		if (cmd.i++ < p_data->argc - 4)
			close(cmd.fd[1]);
		cmd.last_fd = dup(cmd.fd[0]);
		close(cmd.fd[0]);
	}
	if (cmd.last_fd != -1)
		close(cmd.last_fd);
	return (0);
}
