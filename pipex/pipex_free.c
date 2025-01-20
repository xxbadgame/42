/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:09:06 by yannis            #+#    #+#             */
/*   Updated: 2025/01/20 16:02:44 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	all_free_path(char **all_path_str, char **all_path_unit)
{
	free_split(all_path_str);
	free_split(all_path_unit);
}
