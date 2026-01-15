/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alubrano <alubrano@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 09:36:48 by alubrano          #+#    #+#             */
/*   Updated: 2026/01/15 11:41:03 by alubrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	ft_get_line(char *argv, int fds[0])
{
	char	*line;

	while ((line = get_next_line(fds[0])))
	{
		if (ft_strncmp(line, argv, ft_strlen(argv)) == 0 && line[ft_strlen(argv) == '\n'])
		{
			free (line);
			break;
		}
		write(fds[1], &line, ft_strlen(line));
	}
	return;
}

void	ft_here_doc(char **argv, int argc, t_pipex *pipex)
{
	pid_t	pid;
	int		fds[2];

	if (argc > 6)
	ft_error("ERROR EX: here_doc LIMITER cmd cmd1 file", pipex);
	pipex->i = 3;
	pipex->file_out = ft_open(argv[argc - 1], 2, pipex);
	if (pipe(fds))
		perror("Pipe");
	pid = fork();
	if (pid == -1)
		perror("Fork");
	if (pid == 0)
		ft_get_line(argv[2], &fds[0]);
	else
	{
		dup2(fds[0], 0);
		close(fds[1]);
		wait(NULL);
	}
}
