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

void	ft_cmd(t_pipex *pipex)
{
	if (pipe(pipex->fds) == -1)
		perror("Pipe");
	pipex->pids = fork();
	if (pipex->pids == -1)
		perror("Fork");
	if (pipex->pids == 0)
	{
		close(fd[0]);
		dup2(fds[1], 0);
		
	}


}

void	ft_cmd_last(t_pipex *pipex)
{

}

int	ft_open(char *argv, int z, t_pipex	*pipex)
{
	int	rest;

	rest = -1;
	if (z == 0) 
		rest = open(argv, O_WRONLY|O_CREAT|O_TRUNC, 0644);
	else if (z == 1)
		rest = open(argv, O_RDONLY);
	if (rest == -1)
	{
		perror(argv);
		ft_error("Open failed", pipex);
	}
	return(rest);
}

t_pipex	*ft_ini_pipex(int argc, char **argv, char **envp)
{
	t_pipex *pipex;
	
	pipex = ft_calloc(1, sizeof(t_pipex));
	if (!pipex)
		ft_error("Calloc failled", pipex);
	pipex->pids = malloc(sizeof(pid_t) * pipex->n_cmd);
	if (!pipex->pids)
		ft_error("Pipex pids error", pipex); 
	pipex->paths = ft_get_path(envp);
	if (!pipex->paths)
		ft_error("Pipex paths erro", pipex); 
	pipex->n_cmd = argc - 3;
	pipex->i = 2;
	pipex->file_in = -1;
	pipex->file_out = -1;
	pipex->prev_in = -1;
	pipex->fds[0] = -1;
	pipex->fds[1] = -1;
	pipex->file_in = ft_open(argv[1], 1, pipex);
	pipex->file_out = ft_open(argv[argc - 1], 0, pipex);
	pipex->prev_in = pipex->file_in;
	pipex->envp = envp;
	return (pipex);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	int		k;

	k = 0;
	if (argc >= 5)
	{
		pipex = ft_ini_pipex(argc, argv, envp);
		while (pipex->i < argc - 2)
			pipex->pids[k++] = ft_cmd(pipex, argv[pipex->i++]);
		pipex->pids[k] = ft_cmd_last(pipex, argv[argc - 2]);
		while (k >= 0)
			waitpid(pipex->pids[k--], NULL, 0);
		close(fds[1]);
		close(fds[])
		ft_clean_pipex(pipex);
		return (0);
	}
	else 
		ft_printf("ERRO EX : ./pipex file1 cmd1 cmd2 file2");
	return (1);
}
