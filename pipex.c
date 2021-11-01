/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 09:43:27 by jalvarad          #+#    #+#             */
/*   Updated: 2021/11/01 16:16:54 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	kamikaze_son1(t_pipe_var info, char *argv, char **envp, char *infile)
{
	info.fd1 = open(infile, O_RDONLY);
	if (info.fd1 == -1)
	{
		free(info.path);
		info.path = NULL;
		ft_putstr_fd("pipex: ", 1);
		ft_putstr_fd(infile, 1);
		ft_putstr_fd(": No such file or directory or permission denied\n", 1);
	}
	close(info.fd2[READ_END]);
	dup2(info.fd1, STDIN_FILENO);
	close(info.fd1);
	dup2(info.fd2[WRITE_END], STDOUT_FILENO);
	close(info.fd2[WRITE_END]);
	rev_and_exe(info.path, argv, envp);
}

void	kamikaze_son2(t_pipe_var info, char *argv, char **envp, char *outfile)
{
	info.fd1 = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (info.fd1 == -1)
	{
		ft_putstr_fd("pipex: ", 1);
		ft_putstr_fd(outfile, 1);
		ft_putstr_fd(": Permission denied\n", 1);
		exit(-1);
	}
	dup2(info.fd2[READ_END], STDIN_FILENO);
	close(info.fd2[READ_END]);
	dup2(info.fd1, STDOUT_FILENO);
	close(info.fd1);
	rev_and_exe(info.path, argv, envp);
}

void	psycho_parent(t_pipe_var info, char **argv, char **envp)
{
	printf("%d\n",info.fd2[WRITE_END]);
		close(info.fd2[WRITE_END]);
	info.pid = fork();
	if (info.pid == -1)
		exit(-1);
	if (info.pid == 0)
		kamikaze_son2(info, argv[3], envp, argv[4]);
	else
	{
		printf("close %d \n", info.fd2[READ_END]);
		close(info.fd2[READ_END]);
		wait(&info.status);
	}
}

void	divide_proccess(t_pipe_var info, char **argv, char **envp)
{
	if (info.pid == 0)
		kamikaze_son1(info, argv[2], envp, argv[1]);
	else
	{
		free(info.path);
		info.path = search_path(argv[3], envp);
		psycho_parent(info, argv, envp);
		free(info.path);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe_var	info;

	if (argc != 5 )
		return (0);
	
	//pipe(info.fd2);
	if (pipe(info.fd2) == -1)
		exit(-1);
	printf("%d  %d\n", info.fd2[0], info.fd2[1]);
	info.path = search_path(argv[2], envp);
	info.pid = fork();
	if (info.pid == -1)
		exit(-1);
	divide_proccess(info, argv, envp);
	wait(&info.status);
	printf("%d \n", getpid());
	system("lsof -c pipex");
	return (0);
}
