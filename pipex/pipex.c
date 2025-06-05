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

/*Función principal*/
void	pipex(char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd) == -1)
		ft_error("Pipe error");
	pid1 = fork();//CREAR PRIMER HIJO
	if (pid1 == -1)
		ft_error("First child (fork 1) error");
	if (pid1 == 0) //EJECUTAR PRIMER HIJO
		first_child_process(argv, envp, fd);
	else//EJECUTAR EL PADRE
	{
		close(fd[1]);
		pid2 = fork();//CREAR SEGUNDO HIJO
		if (pid2 == -1)
			ft_error("Second child (fork 2) error");
		if (pid2 == 0) //EJECUTAR SEGUNDO HIJO
			second_child_process(argv, envp, fd);
		else//EJECUTAR AL PADRE
			close(fd[0]);
	}
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	first_child_process(char **argv, char **envp, int *fd)
{
	int	infile;

	(void)envp;
	infile = open_file(argv[1], 0);
	if (infile == -1)
		ft_error("Infile error");
	close(fd[0]);
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	//execute(argv[2], envp); EJECUTAS COMANDO CON execve
	execlp("/bin/ls", "ls", "-l", NULL);
}

void	second_child_process(char **argv, char **envp, int *fd)
{
	int	outfile;

	(void)envp;
	outfile = open_file(argv[4], 1);
	if (outfile == -1)
		ft_error("Outfile error");
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[0]);
	//execute(argv[3], envp); EJECUTAS COMANDO CON execve
	execlp("/usr/bin/wc", "wc", NULL);
}
