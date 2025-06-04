/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:41:39 by marvin            #+#    #+#             */
/*   Updated: 2025/06/03 13:41:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//Llamar a mi función principal pipex(argv, envp);
int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
		arg_error();
	pipe(fd);
	if (pipe(fd) == -1)
		error();
	pid = fork();	//CREAR PRIMER HIJO
	if (pid == -1)
		error();
	if (pid == 0)	//EJECUTAR PRIMER HIJO	"CHILD"
		first_child_process(argv, envp, fd);
	else	//EJECUTAR EL PADRE	"PARENT"
	{
		close(fd[1]);
		pid = fork();	//CREAR SEGUNDO HIJO
		if (pid == -1)
			error();
		if (pid == 0)	//EJECUTAR SEGUNDO HIJO
			second_child_process(argv, envp, fd);
		else	//EJECUTAR AL PADRE
			close(fd[0]);
	}
	//NOSE QUE ES
	waitpid(pid, NULL, 0);
	return (0);
}
