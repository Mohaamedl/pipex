/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 21:02:36 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/03 21:02:30 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

static char	*find_executable(char **allpath, char *cmd)
{
	int		i;
	char	*exec;
	char	*path_part;

	i = -1;
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, cmd);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
			return (exec);
		free(exec);
	}
	return (NULL);
}

static char	*search_in_path(char *cmd, char **env)
{
	char	**allpath;
	char	*result;

	allpath = ft_split(my_getenv("PATH", env), ':');
	if (!allpath)
		return (NULL);
	result = find_executable(allpath, cmd);
	ft_free_tab(allpath);
	return (result);
}

static char	*get_path(char *cmd, char **env)
{
	char	*result;

	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	result = search_in_path(cmd, env);
	return (result);
}

static void	handle_exec_error(char **s_cmd, char *path)
{
	ft_putstr_fd("pipex: command not found: ", 2);
	ft_putendl_fd(s_cmd[0], 2);
	ft_free_tab(s_cmd);
	if (path)
		free(path);
	exit(127);
}

void	exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = parse_command(cmd);
	if (!s_cmd || !s_cmd[0])
	{
		ft_putendl_fd("pipex: invalid command", 2);
		ft_free_tab(s_cmd);
		exit(127);
	}
	path = get_path(s_cmd[0], env);
	if (!path)
		handle_exec_error(s_cmd, NULL);
	if (execve(path, s_cmd, env) == -1)
		handle_exec_error(s_cmd, path);
}
