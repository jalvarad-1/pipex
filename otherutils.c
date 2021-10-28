/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otherutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 11:40:36 by jalvarad          #+#    #+#             */
/*   Updated: 2021/09/25 11:57:01 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	while (*s)
		write(fd, s++, 1);
}

void	rev_and_exe(char *path, char *argv, char **envp)
{
	char	**cmd_args;

	cmd_args = ft_split(argv, ' ');
	execve(path, cmd_args, envp);
}

void	error_of_cmd(char **cmd)
{
	ft_putstr_fd(cmd[0], 1);
	ft_putstr_fd(": command not found\n", 1);
}

static char	*search_path_aux(char **split_paths, char **cmd)
{
	char	*aux;
	char	*path;
	int		i;

	i = 0;
	while (split_paths[i])
	{
		aux = ft_strjoin(split_paths[i], "/");
		path = ft_strjoin(aux, cmd[0]);
		free(aux);
		aux = NULL;
		if (access(path, X_OK) == 0)
		{
			del_split(cmd);
			del_split(split_paths);
			return (path);
		}
		free(path);
		i++;
	}
	error_of_cmd(cmd);
	del_split(cmd);
	del_split(split_paths);
	return (0);
}

char	*search_path(char *argv, char **envp)
{
	char	*path;
	char	**split_paths;
	char	**cmd;
	int		i;

	i = 0;
	cmd = ft_split(argv, ' ');
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	if (!envp[i])
	{
		return (NULL);
	}
	split_paths = ft_split(envp[i] + 5, ':');
	path = search_path_aux(split_paths, cmd);
	return (path);
}
