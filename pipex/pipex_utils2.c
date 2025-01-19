/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 09:56:32 by yannis            #+#    #+#             */
/*   Updated: 2025/01/19 10:41:24 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

int	free_split(char **str_spl)
{
	int	i;

	i = 0;
	while (str_spl[i])
		free(str_spl[i++]);
    free(str_spl);
	return (0);
}

int	free_cmds(int start, int argc, char ***cmds)
{
	int	i;
	int	y;

	i = start;
	y = 0;
	while (i < argc)
	{
		y = 0;
		while (cmds[i - start][y])
			free(cmds[i - start][y++]);
		free(cmds[i - start]);
		i++;
	}
	free(cmds);
	return (0);
}

void	create_pipe(t_pipex *p_data, int *fd, int j)
{
	if (p_data->argv[j + 2] != NULL)
	{
		if (pipe(fd) == -1)
		{
			perror("Pipe failed");
			exit(1);
		}
	}
}

void	close_fds(int in_fd, int out_fd)
{
	if (in_fd != -1)
		close(in_fd);
	if (out_fd != -1)
		close(out_fd);
}

void	heredoc_fds(t_pipex *p_data)
{
	int	stdin_backup;

	stdin_backup = dup(STDIN_FILENO);
	heredoc_run(p_data->argv);
	p_data->infile = dup(STDIN_FILENO);
	p_data->outfile = open(p_data->argv[p_data->argc - 1],
			O_WRONLY | O_CREAT | O_APPEND, 0777);
	dup2(stdin_backup, STDIN_FILENO);
	close(stdin_backup);
}