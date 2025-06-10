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
		ft_error("pipe error");
	pid1 = fork();//CREAR PRIMER HIJO
	if (pid1 == -1)
		ft_error("first child (fork 1) error");
	if (pid1 == 0) //EJECUTAR PRIMER HIJO
		//close(fd[0]);
		first_child_process(argv, envp, fd);
	else//EJECUTAR EL PADRE
	{
		//close(fd[1]);
		pid2 = fork();//CREAR SEGUNDO HIJO
		if (pid2 == -1)
			ft_error("second child (fork 2) error");
		if (pid2 == 0) //EJECUTAR SEGUNDO HIJO
			//close(fd[1]);
			second_child_process(argv, envp, fd);
		//else//EJECUTAR AL PADRE
		//	close(fd[0]);
	}
	//Proceso padre cierra ambos extremos de la tubería y espera a los hijos
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	first_child_process(char **argv, char **envp, int *fd)
{
	int		infile;
	char	**cmd_args;

	(void)envp;
	infile = open_file(argv[1], 0);
	if (infile == -1)
		ft_error("infile error");
	close(fd[0]);
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	cmd_args = ft_split(argv[2], ' ');
	if (!cmd_args)
		ft_error("memory allocation error");
	execute_cmd(cmd_args, envp);
	free_paths(cmd_args);
}

void	second_child_process(char **argv, char **envp, int *fd)
{
	int		outfile;
	char	**cmd_args;

	(void)envp;
	outfile = open_file(argv[4], 1);
	if (outfile == -1)
		ft_error("outfile error");
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[0]);
	cmd_args = ft_split(argv[3], ' ');
	if (!cmd_args)
		ft_error("memory allocation error");
	execute_cmd(cmd_args, envp);
	free_paths(cmd_args);
}
