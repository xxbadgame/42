/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:46:12 by yannis            #+#    #+#             */
/*   Updated: 2025/01/20 17:45:44 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_getenv(char *var_name, char *envp[])
{
	char	**env_variable;
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		env_variable = ft_split(envp[i], '=');
		if (ft_strncmp(env_variable[0], var_name, ft_strlen(var_name)) == 0)
		{
			free_split(env_variable);
			return (envp[i]);
		}
		free_split(env_variable);
		i++;
	}
	return (NULL);
}

void create_path(char	**all_path_unit, char	**all_path_str, char **cmd, int i)
{
	int		size_path;
	char	*full_path;

	size_path = ft_strlen(all_path_unit[i]) + 1 + ft_strlen(cmd[0]) + 1;
	full_path = malloc(size_path);
	if (!full_path)
		return (all_free_path(all_path_str, all_path_unit), NULL);
	ft_strlcpy(full_path, all_path_unit[i], ft_strlen(all_path_unit[i])
		+ 1);
	ft_strlcat(full_path, "/", ft_strlen(all_path_unit[i++]) + 2);
	ft_strlcat(full_path, cmd[0], size_path);
	if (access(full_path, X_OK) == 0)
		return (all_free_path(all_path_str, all_path_unit), full_path);
	free(full_path);
}

char	*ft_path_to_cmd(char **cmd, char *envp[])
{
	char	**all_path_str;
	char	**all_path_unit;
	int		i;

	i = 0;
	all_path_str = ft_split(ft_getenv("PATH", envp), '=');
	if (!all_path_str)
		return (NULL);
	all_path_unit = ft_split(all_path_str[1], ':');
	if (!all_path_unit)
		return (free(all_path_str), NULL);
	while (all_path_unit[i] != NULL)
		create_path(all_path_unit[i], all_path_str, cmd, i);
	return (all_free_path(all_path_str, all_path_unit), NULL);
}

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
		if (cmd.last_fd == -1)
			return (-1);
		close(cmd.fd[0]);
	}
	if (cmd.last_fd != -1)
		close(cmd.last_fd);
	return (0);
}
