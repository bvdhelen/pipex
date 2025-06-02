/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex2proc1pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:27:29 by marvin            #+#    #+#             */
/*   Updated: 2025/06/02 17:27:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>		//Utilizar la función dup2()
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#define READ_END	0	//index pipe extremo lectura
#define WRITE_END	1	//index pipe extremo escritura

#define FILE_NAME	"file.txt"	//Nombre del archivo donde escribir

int	main(int argc, char **argv)
{
	int	fd1[2];
	int	fd2;
	int	status; //realizar el wait que hace el padre (fork) para cada hijo
	int	pid; //identificador del proceso de los hijos

	pipe(fd1);	//comunica ls y wc
	pid = fork();	//crear el primer hijo
	if (pid == 0)	//ejecución del hijo 1, ejecuta "ls -l"
	{
		close(fd1[READ_END]);	//cerrar extremo no necesario del pipe
		dup2(fd1[WRITE_END], STDOUT_FILENO);	//redirigir la escritura
		close(fd1[WRITE_END]);

		execlp("/bin/ls", "ls", "-l", NULL);	//EJECUTAR LO QUE QUIERES, decir donde está y como lo llamas
	}
	else	//ejecución del padre
	{
		close(fd1[WRITE_END]);	//cerrar extremo no necesario del pipe
		pid = fork();	//crear el segundo hijo
		if (pid == 0)	//ejecución del hijo 2, ejecuta "wc"
		{
			fd2 = open(FILE_NAME, O_WRONLY);	//abrir el archivo
			dup2(fd1[READ_END], STDIN_FILENO);	//redirigir la lectura
			close(fd1[READ_END]);

			dup2(fd2, STDOUT_FILENO);	//redirigir la escritura

			execlp("/usr/bin/wc", "wc", NULL);	//EJECUTAR LO QUE QUIERES, decir donde está y como lo llamas
		}
		else	//ejecución del padre
		{
			close(fd1[READ_END]);	//cerrar extremo no necesario
		}
	}
	//wait para cada hijo ¿?
	wait(&status);
	wait(&status);
	return (0);
}
