/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:09:06 by yannis            #+#    #+#             */
/*   Updated: 2025/01/07 16:47:42 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

char *ft_getenv(char *var_name, char *envp[])
{
    char    **env_variable;
    int     i;

    i = 0;
    while (envp[i] != NULL)
    {
        env_variable = ft_split(envp[i], '=');
        if (ft_strncmp(env_variable[0], var_name, ft_strlen(var_name)) == 0)
            return envp[i];
        i++;
    }
    return NULL;
}

char *ft_path_to_cmd(char **cmd, char *envp[])
{
    char *path_var;
    char *all_path_str;
    char **all_path_unit;
    int size_path;
    char *full_path;
    int   i;
     
    i = 0;
    path_var = ft_getenv("PATH", envp);
    all_path_str = ft_split(path_var, '=')[1];
    all_path_unit = ft_split(all_path_str, ':');

    while (all_path_unit[i] != NULL)
    { 
        size_path = ft_strlen(all_path_unit[i])+ 1 + ft_strlen(cmd[0]) + 1;
        full_path = malloc(size_path);
        ft_strlcpy(full_path, all_path_unit[i], ft_strlen(all_path_unit[i]) + 1);
        ft_strlcat(full_path, "/", ft_strlen(all_path_unit[i]) + 2);
        ft_strlcat(full_path, cmd[0], size_path);
        if (access(full_path, X_OK) == 0)
            return full_path;
        i++;
    }
    free(full_path);
    return NULL;
}