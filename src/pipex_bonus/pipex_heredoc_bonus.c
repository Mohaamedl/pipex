/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 21:40:00 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/03 21:40:00 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

void	here_doc_put_in(char **av, int *p_fd)
{
	char	*ret;

	close(p_fd[0]);
	ft_putstr_fd("> ", 1);
	while (1)
	{
		ret = get_next_line(0);
		if (!ret)
			break ;
		if (ft_strncmp(ret, av[2], ft_strlen(av[2])) == 0
			&& ret[ft_strlen(av[2])] == '\n')
		{
			free(ret);
			break ;
		}
		ft_putstr_fd(ret, p_fd[1]);
		free(ret);
		ft_putstr_fd("> ", 1);
	}
	close(p_fd[1]);
	exit(0);
}

void	here_doc(char **av)
{
	int		p_fd[2];
	pid_t	pid;

	if (pipe(p_fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (!pid)
		here_doc_put_in(av, p_fd);
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		close(p_fd[0]);
		wait(NULL);
	}
}
