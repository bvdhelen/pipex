/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:30:31 by marvin            #+#    #+#             */
/*   Updated: 2025/06/26 20:30:31 by marvin           ###   ########.fr       */
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
		ft_error("invalid access mode error", 1);
	return (fd);
}

/*Función para liberar memoria de las rutas*/
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

/*Función para comprobar si el acceso está permitido 
(comando encontrado) pero no ejecutable
código de error 126 -> comando encontrado pero no ejecutable*/
void	check_access(char *path, char **cmd)
{
	if (access(path, X_OK) == -1)
	{
		free(path);
		free_paths(cmd);
		ft_error("permission denied error", 126);
	}
}
