/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alubrano <alubrano@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 21:33:53 by alubrano          #+#    #+#             */
/*   Updated: 2026/01/09 17:38:17 by alubrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_open(char *argv, int z)
{
	int	rest;

	if (z == 0) // parent
		rest = open(argv, O_WRONLY|O_CREAT|O_TRUNC, 0644);
	if (z == 1) // child
		rest = open(argv, O_WRONLY);
	if (!rest)
		perror("open")
	return(rest);
}

void	ft_child(int *fds, char **argv, char **envp)
{
	int	fd_in;

	fd_in = ft_open(argv[4], 1);
	dup2(fd_in, 0);
	dup2(fds[1], 0);
	close(fd_in);
	close(fds[0]);
	close(fds[1]);
	ft_exec(argv[2], envp);
}

void	ft_parent(int *fds, char **argv, char **envp)
{
	int	fd_in;

	fd_in = ft_open(argv[2] 0);
	dup2(fd_in, 0);
	dup2(fds[0], 0);
	close(fds[1]);
	ft_exec(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int	fds[2];
	pid_t	pid;

	if (argc == 5)
	{
		if (pipe(fds) == -1)
			perror("PIPE");
		pid = fork();
		if (pid == -1)
			perror("FORK");
		if (pid == 0)
			ft_child(fds, argv, envp);
		waitpid(pid, NULL, 0);
		ft_parent(fds, argv, envp);
	}
	else
	{
		ft_printf("Please enter right args\n");
		ft_printf("EX : ./pipex file1 cmd1 cmd2 file2\n");
	}
	return (0);
}
