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

/*Función error de argumentos*/
void	arg_error(void)
{
	ft_putstr_fd("\033[31mError: Bad arguments\n\e[0m", 2);
	ft_putstr_fd("Usage:\t ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
}

/*Función error principal*/
void	ft_error(char *message)
{
	ft_putstr_fd("\033[31mError: \n\e[0m", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	//perror(message);
	exit(1);
}

/*Función para verificar si no se pasa comando*/
int	empty_cmd(const char *cmd)
{
	while (*cmd)
	{
		if (!ft_isspace(*cmd))
			return (0);
		cmd++;
	}
	return (1);
}

/*Función principal que ejecuta mi pipex*/
int	main(int argc, char **argv, char **envp)
{
	if (argc == 5)
	{
		if (empty_cmd(argv[2]) || empty_cmd(argv[3]))
			ft_error("empty or invalid command");
		pipex(argv, envp);
	}
	else
		arg_error();
	return (0);
}
