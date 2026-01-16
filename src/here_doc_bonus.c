/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alubrano <alubrano@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 09:36:48 by alubrano          #+#    #+#             */
/*   Updated: 2026/01/16 18:13:49 by alubrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	ft_open(char *argv, int z, t_pipex	*pipex)
{
	int	rest;

	rest = -1;
	if (z == 0)
		rest = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (z == 1)
		rest = open(argv, O_RDONLY);
	else if (z == 2)
		rest = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (rest == -1)
	{
		perror(argv);
		ft_error("Open failed", pipex);
	}
	return (rest);
}

void	ft_get_line(char *argv, int fds[], t_pipex *pipex)
{
	char	*line;

	close(fds[0]);
	while ((line = get_next_line(0)) && line != NULL)
	{
		if (ft_strncmp(line, argv, ft_strlen(argv)) == 0
			&& line[ft_strlen(argv)] == '\n')
		{
			free (line);
			break ;
		}
		write(fds[1], line, ft_strlen(line));
		free(line);
	}
	close(fds[1]);
	ft_clean_pipex(pipex);
	exit (1);
}

void	ft_here_doc(char **argv, int argc, t_pipex *pipex)
{
	pid_t	pid;
	int		fds[2];

	if (argc < 6)
		ft_error("ERROR EX: here_doc LIMITER cmd cmd1 file", pipex);
	pipex->file_out = ft_open(argv[argc - 1], 2, pipex);
	pipex->i = 3;
	if (pipe(fds) == -1)
		perror("Pipe");
	pid = fork();
	if (pid == -1)
		perror("Fork");
	if (pid == 0)
		ft_get_line(argv[2], fds, pipex);

	else
	{
		close(fds[1]);
		wait(NULL);
		pipex->prev_in = fds[0];
	}
}
