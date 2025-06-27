/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:28:52 by marvin            #+#    #+#             */
/*   Updated: 2025/06/02 17:28:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include "get_next_line/get_next_line.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>

# define READ_END	0	//index pipe extremo lectura
# define WRITE_END	1	//index pipe extremo escritura

int		is_absolute_path(const char *cmd);
char	*check_direct_path(const char *cmd);
char	*join_paths(const char *folder, const char *cmd);
char	*get_cmd_path(char *cmd, char **envp);
void	execute_cmd(char **cmd, char **envp);

int		open_file(const char *file, int access_mode);
void	free_paths(char **paths);

void	pipex(char **argv, char **envp);
void	first_child_process(char **argv, char **envp, int *fd);
void	second_child_process(char **argv, char **envp, int *fd);

void	arg_error(void);
void	ft_error(char *message, int code);
int		empty_cmd(const char *cmd);
int		main(int argc, char **argv, char **envp);

#endif
