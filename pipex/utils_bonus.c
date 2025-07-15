/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:40:13 by marvin            #+#    #+#             */
/*   Updated: 2025/07/15 12:40:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*Función para abrir archivos*/
int	open_file_bonus(const char *file, int access_mode)
{
	int	fd;

	if (access_mode == 0)
		fd = open(file, O_RDONLY);
	else if (access_mode == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (access_mode == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (access_mode == -1)
		ft_error("invalid access mode error", 1);
	return (fd);
}
