/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:17:34 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/03 19:17:45 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include "../libft/inc/get_next_line.h"
# include "../libft/inc/libft.h"

char	**parse_command(char *cmd);
void	ft_free_tab(char **tab);
void	exit_handler(int n_exit);
int		open_file(char *file, int in_or_out);
char	*my_getenv(char *name, char **env);
void	exec(char *cmd, char **env);
void	here_doc_put_in(char **av, int *p_fd);
void	here_doc(char **av);
void	do_pipe(char *cmd, char **env);

#endif
