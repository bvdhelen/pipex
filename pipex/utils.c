/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:41:33 by marvin            #+#    #+#             */
/*   Updated: 2025/06/03 13:41:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Función para concatenar la ruta con el comando*/
char	*join_paths(const char *folder, const char *cmd)
{
	char	*full_path;
	char	*result;

	full_path = ft_strjoin(folder, "/");
	result = ft_strjoin(full_path, cmd);
	free(full_path);
	return (result);
}

/*Función para encontrar la ruta del comando*/
char	*get_cmd_path(char *cmd, char **envp)
{
	int		i;
	char	*path;
	char	**paths;

	i = 0;
	while (envp[i] && !ft_strnstr(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		path = join_paths(paths[i], cmd);
		if (!path)
		{
			free_paths(paths);
			return (NULL);
		}
		if (access(path, X_OK) == 0)
		{
			free_paths(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_paths(paths);
	return (NULL);
}

/*Función para comprobar si es una ruta absoluta o relativa*/
int	is_absolute_path(const char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp("/", cmd, 1) == 0)
		return (1);
	if (ft_strncmp("./", cmd, 2) == 0)
		return (1);
	if (ft_strncmp("../", cmd, 3) == 0)
		return (1);
	return (0);
}

char	*check_direct_path(const char *cmd)
{
	if (is_absolute_path(cmd) && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

/*Función para ejecutar el comando*/
void	execute_cmd(char **cmd, char **envp)
{
	char	*path;

	path = check_direct_path(cmd[0]);
	if (!path)
		path = get_cmd_path(cmd[0], envp);
	if (!path)
	{
		free_paths(cmd);
		ft_error("command not found in PATH error");
	}
	if (execve(path, cmd, envp) == -1)
	{
		free(path);
		free_paths(cmd);
		ft_error("execve error");
	}
}
