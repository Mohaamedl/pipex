/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:57:34 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/03 21:04:45 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include "libft/inc/get_next_line.h"
# include "libft/inc/libft.h"

void	ft_free_tab(char **tab);
void	exit_error(char *msg);
char	*my_getenv(char *name, char **env);
char	*get_path(char *cmd, char **env);
char	*find_executable(char **allpath, char *cmd);
void	exec(char *cmd, char **env);
void	child_process(char **av, int *p_fd, char **env);
void	parent_process(char **av, int *p_fd, char **env);

#endif
