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

/*Función para abrir archivos*/
int	open_file(const char *file, int access_mode)
{
	int	fd;

	if (access_mode == 0)
		fd = open(file, O_RDONLY);
	if (access_mode == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (access_mode == -1)
		exit(0);
	return (fd);
}

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	*join_paths(const char *folder, const char *cmd)
{
	char	*full_path;
	char	*result;

	full_path = ft_strjoin(folder, "/");
	result = ft_strjoin(full_path, cmd);
	free(full_path);
	return (result);
}

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

void	execute_cmd(char **cmd, char **envp)
{
	char	*path;

	path = get_cmd_path(cmd[0], envp);
	if (!path)
	{
		free_paths(cmd);
		ft_error("get command path error");
	}
	if (execve(path, cmd, envp) == -1)
	{
		free(path);
		free_paths(cmd);
		ft_error("execve error");
	}
}
