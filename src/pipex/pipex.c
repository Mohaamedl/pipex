/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:45:36 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/03 21:03:30 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	child_process(char **av, int *p_fd, char **env)
{
	int	fd;

	if (access(av[1], R_OK) != 0)
	{
		perror(av[1]);
		fd = open("/dev/null", O_RDONLY);
	}
	else
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			perror(av[1]);
			fd = open("/dev/null", O_RDONLY);
		}
	}
	dup2(fd, STDIN_FILENO);
	dup2(p_fd[1], STDOUT_FILENO);
	close(p_fd[0]);
	close(p_fd[1]);
	close(fd);
	exec(av[2], env);
}

void	parent_process(char **av, int *p_fd, char **env)
{
	dup2(p_fd[0], STDIN_FILENO);
	close(p_fd[0]);
	exec(av[3], env);
}

void	handle_parent_process(char **av, int *p_fd, char **env)
{
	int		fd_out;

	close(p_fd[1]);
	fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		perror(av[4]);
		exit(1);
	}
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	parent_process(av, p_fd, env);
}

int	main(int ac, char **av, char **env)
{
	int		p_fd[2];
	pid_t	pid;

	if (ac != 5)
	{
		ft_putendl_fd("Usage: ./pipex infile cmd1 cmd2 outfile", 2);
		exit(EXIT_FAILURE);
	}
	if (pipe(p_fd) == -1)
		exit_error();
	pid = fork();
	if (pid == -1)
		exit_error();
	if (pid == 0)
		child_process(av, p_fd, env);
	else
		handle_parent_process(av, p_fd, env);
	return (0);
}
