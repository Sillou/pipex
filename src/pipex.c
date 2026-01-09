/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alubrano <alubrano@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 21:33:53 by alubrano          #+#    #+#             */
/*   Updated: 2026/01/09 15:28:44 by alubrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_open(char *argv, int z)
{
	int	rest;

	if (z == 0)
		rest = open(argv, O_RDONLY);
	if (z == 1)
		rest = open(argv, O_WRONLY);
	return(rest);
}

void	ft_free_cmd(char **t_cmd)
{
	int	x;

	x = 0;
	while (t_cmd[x])
		free(t_cmd[x]);
	free(t_cmd);
}

void	ft_exec(char *argv, char **envp)
{
	char	**t_cmd;
	char	*path;

	path = ft_get_path(envp);
	t_cmd = ft_split(argv, ' ');
	if (execv(path, t_cmd) == -1)
		ft_putendl_fd("CMD not found", 2);
	ft_free_cmd(t_cmd);

}

void	ft_parent(int *fds, char **argv, char **envp)
{
	int	fd;

	fd = ft_open(argv[1], 1);
	dup2(fd, 0);
	dup2(fds[1], 1);
	close(fds[1]);
	ft_exec(argv[2], envp);
}

void	ft_child(int *fds, char **argv, char **envp)
{
	int	fd;

	fd = ft_open(argv[4], 0);
	dup2(fd, 0);
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
		ft_child(fds, argv, envp);
		ft_parent(fds, argv, envp);
	}
	else
	{
		ft_printf("Please enter right args\n");
		ft_printf("EX : ./pipex file1 cmd1 cmd2 file2\n");
	}
	return (0);
}
