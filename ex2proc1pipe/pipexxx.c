/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexxx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 20:25:07 by marvin            #+#    #+#             */
/*   Updated: 2025/06/27 20:25:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Función para ejecutar dos comandos conectados por una tubería (pipe)*/
void	pipex(char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd) == -1)
		ft_error("pipe error", 1);
	pid1 = fork();//CREAR PRIMER HIJO
	if (pid1 == -1)
		ft_error("first child (fork 1) error", 1);
	if (pid1 == 0) //EJECUTAR PRIMER HIJO
		//close(fd[0]);
		first_child_process(argv, envp, fd);
	else//EJECUTAR EL PADRE
	{
		//close(fd[1]);
		pid2 = fork();//CREAR SEGUNDO HIJO
		if (pid2 == -1)
			ft_error("second child (fork 2) error", 1);
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

//Explicación de los códigos de salida
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0); // Captura el estado de terminación del segundo hijo

	if (WIFEXITED(status)) // PASO 1: ¿Terminó el segundo hijo de forma normal?
    	exit(WEXITSTATUS(status)); // PASO 2: Si sí, salimos de pipex con SU código de salida.
	else // Si el hijo no terminó normalmente (ej. fue matado por una señal)
    	exit(1); // Salimos con un código de error genérico (o el que decida el sujeto de Pipex)