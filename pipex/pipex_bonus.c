/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:40:10 by marvin            #+#    #+#             */
/*   Updated: 2025/07/15 12:40:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*Función para ejecutar varios comandos conectados por varias tuberías (pipes)*/
void	pipex_bonus(int argc, char **argv, char **envp)
{
	int		i;
	int		fd[2];
	int		infile;
	int		outfile;
	int		prev_fd = -1;
	pid_t	pid;

	infile = open_file_bonus(argv[1], 0); // Abrir archivo de entrada para lectura
	outfile = open_file_bonus(argv[argc - 1], 2); // Abrir archivo de salida para escritura
	i = 2; // Comenzamos desde el primer comando: argv[2] hasta el penúltimo comando
	while (i < argc - 2)
	{
		if (pipe(fd) == -1) // Crear un nuevo pipe
			ft_error("pipe error", 1);
		pid = fork(); // Crear un proceso hijo
		if (pid == -1)
			ft_error("fork error", 1);
		if (pid == 0) // Proceso hijo
		{
			if (i == 2)
				dup2(infile, STDIN_FILENO); // Primer comando: lee del archivo de entrada
			else
				dup2(prev_fd, STDIN_FILENO); // Resto de comandos: leen del pipe anterior
			dup2(fd[1], STDOUT_FILENO); // Redirigir salida al pipe actual
			close(fd[0]); // Cerramos lectura del pipe actual (no se necesita en el hijo)
			if (prev_fd != -1)
				close(prev_fd); // Cerramos lectura anterior (ya duplicada)
			execute_cmd(ft_split(argv[i], ' '), envp); // Ejecutamos el comando actual (dividido por espacios)
		}
		close(fd[1]); // Proceso padre: Cerramos escritura del pipe actual
		if (prev_fd != -1)
			close(prev_fd); // Cerramos lectura anterior (ya usada por el hijo anterior)
		prev_fd = fd[0]; // Guardamos la lectura actual para el siguiente comando
		i++; // Siguiente comando
	}
	pid = fork(); // Último comando (el que escribe en outfile)
	if (pid == -1)
		ft_error("last fork error", 1);
	if (pid == 0)
	{
		dup2(prev_fd, STDIN_FILENO); // Lee del último pipe anterior
		dup2(outfile, STDOUT_FILENO); // Escribe en el archivo de salida
		execute_cmd(ft_split(argv[i], ' '), envp); // Ejecutamos el último comando
	}
	close(prev_fd); // Padre: cerramos la lectura del último pipe
	while (wait(NULL) > 0); // Esperamos a que terminen todos los hijos
}
