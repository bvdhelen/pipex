/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:41:36 by marvin            #+#    #+#             */
/*   Updated: 2025/06/03 13:41:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(const char *file, int access_mode)
{
	int	fd;

	if (access_mode == 0)
		fd = open(file, O_RDONLY);
	if (access_mode == 1)
		fd = open(file, O_WRONLY);
	if (access_mode == -1)
		exit(0);
	return (fd);
}

void	first_child_process(char **argv, char **envp, int *fd)
{
	(void)argv;
	(void)envp;
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	//ejecutas comando con execve
	execlp("/bin/ls", "ls", "-l", NULL);
	//execute(argv[2], envp);
}

void	second_child_process(char **argv, char **envp, int *fd)
{
	(void)envp;
	//int	file_out;

	//file_out = open_file(argv[4], 1);
	open_file(argv[4], 1);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	//redirigir la escritura
	dup2(fd[1], STDOUT_FILENO);
	//ejecutas comando con execve
	execlp("/usr/bin/wc", "wc", NULL);
	//execute(argv[3], envp);
}

/*Ejecutar el proceso hijo, coger el fichero de entrada, 
meter la salida en un pipe y cerrar con la función que ejecuta el comando */
/*void	child_process(char **argv, char **envp, int	*fd)
{
	int	filein;

	filein = open_file(argv[1], 0);
	//dup2(fd[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	close(fd[0]);
	//Redirigir la escritura
	dup2(fd[1], STDOUT_FILENO);
	//Ejecutar comando
	execute(argv[2], envp);
}
*/