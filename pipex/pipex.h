/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 22:50:30 by yannis            #+#    #+#             */
/*   Updated: 2025/01/19 10:01:09 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		argc;
	char	**argv;
}			t_pipex;

char		*ft_getenv(char *var_name, char *envp[]);
char		*ft_path_to_cmd(char **cmd, char *envp[]);
void		heredoc_fds(t_pipex *p_data);
void		heredoc_run(char **argv);
void 		close_fds(int in_fd, int out_fd);
void		create_pipe(t_pipex *p_data, int *fd, int j);
int			free_cmds(int start, int argc, char ***cmds);
int			free_split(char **str_spl);

#endif