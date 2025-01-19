/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:09:06 by yannis            #+#    #+#             */
/*   Updated: 2025/01/19 17:07:42 by yannis           ###   ########.fr       */
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

char	*ft_path_to_cmd(char **cmd, char *envp[])
{
	char	**all_path_str;
	char	**all_path_unit;
	int		size_path;
	char	*full_path;
	int		i;

	i = 0;
	all_path_str = ft_split(ft_getenv("PATH", envp), '=');
	all_path_unit = ft_split(all_path_str[1], ':');
	while (all_path_unit[i] != NULL)
	{
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
	return (all_free_path(all_path_str, all_path_unit), NULL);
}
