/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:50:36 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/04 20:30:00 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

void	do_pipe(char *cmd, char **env)
{
	pid_t	pid;
	int		p_fd[2];

	if (pipe(p_fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (!pid)
	{
		close(p_fd[0]);
		dup2(p_fd[1], 1);
		close(p_fd[1]);
		exec(cmd, env);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		close(p_fd[0]);
		wait(NULL);
	}
}

static void	handle_here_doc_mode(int ac, char **av, int *fd_out, int *i)
{
	if (ac < 6)
		exit_handler(1);
	*i = 3;
	*fd_out = open_file(av[ac - 1], 2);
	here_doc(av);
}

static void	handle_normal_mode(int ac, char **av, int *fd_out, int *i)
{
	int	fd_in;

	*i = 2;
	if (ac == 5)
		*fd_out = -1;
	else
		*fd_out = open_file(av[ac - 1], 1);
	if (access(av[1], R_OK) != 0)
	{
		perror(av[1]);
		fd_in = open("/dev/null", O_RDONLY);
	}
	else
		fd_in = open_file(av[1], 0);
	dup2(fd_in, 0);
	close(fd_in);
}

int	main(int ac, char **av, char **env)
{
	int		i;
	int		fd_out;

	if (ac < 5)
		exit_handler(1);
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
		handle_here_doc_mode(ac, av, &fd_out, &i);
	else
		handle_normal_mode(ac, av, &fd_out, &i);
	while (i < ac - 2)
		do_pipe(av[i++], env);
	if (ac == 5)
	{
		fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out == -1)
		{
			perror(av[ac - 1]);
			exit(1);
		}
	}
	dup2(fd_out, 1);
	close(fd_out);
	exec(av[ac - 2], env);
}
