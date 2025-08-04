/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 21:35:00 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/03 21:35:00 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*try_path_combination(char **allpath, char **s_cmd)
{
	int		i;
	char	*exec;
	char	*path_part;

	i = -1;
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
			return (exec);
		free(exec);
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	char	**allpath;
	char	**s_cmd;
	char	*result;

	allpath = ft_split(my_getenv("PATH", env), ':');
	if (!allpath)
		return (ft_strdup(cmd));
	s_cmd = ft_split(cmd, ' ');
	if (!s_cmd || !s_cmd[0])
	{
		ft_free_tab(allpath);
		ft_free_tab(s_cmd);
		return (ft_strdup(cmd));
	}
	result = try_path_combination(allpath, s_cmd);
	ft_free_tab(allpath);
	ft_free_tab(s_cmd);
	if (result)
		return (result);
	return (ft_strdup(cmd));
}
