/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alubrano <alubrano@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 09:36:48 by alubrano          #+#    #+#             */
/*   Updated: 2026/01/15 10:59:00 by alubrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>


void	ft_here_doc(char *argv, int argc, t_pipex *pipex)
{
	char	*line;
	pid_t	pid;
	int		fds[2];

	if (argc > 6)
		ft_error("ERROR EX: here_doc LIMITER cmd cmd1 file", pipex);
	pid = fork();
	if (pid == -1)
		perror("Fork");
	if (pid == 0)
	{
		while ((line = get_next_line(fds[0])))
		{
			if (ft_strncmp(line, argv, ft_strlen(argv)))
				return;
			write(fds[1], &line, ft_strlen(line));
		}
	}
	else
	{
		dup2(fds[0], 0);
		close(fds[1]);
		wait(NULL);
	}
}
