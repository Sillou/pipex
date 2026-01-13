/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alubrano <alubrano@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 17:37:28 by alubrano          #+#    #+#             */
/*   Updated: 2026/01/09 17:38:09 by alubrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_get_path(t_pipex *pipex, char *argv)
{
	int		i;
	char	*line;

	i = 0;
	while (pipex->envp[i])
	{
		if (ft_strnstr(pipex->envp[i], "PATH=", 5) == pipex->envp[i])
		{
			line = pipex->envp[i];
			break;
		}
		i++;
	}
	if (!line)
		ft_error("Path not found", pipex);
	pipex->paths = ft_split(line, ":");
	if (!pipex->paths)
		ft_error("Path split Error", pipex);
}

void	ft_exec(t_pipex *pipex, char *argv)
{
	char	**t_cmd;
	char	*path;

	path = ft_get_path(pipex, argv);
	t_cmd = ft_split(argv, ' ');
	if (execv(path, t_cmd) == -1)
		ft_putendl_fd("CMD not found", 2);
	ft_free_cmd(t_cmd);

}

void	ft_clean_pipex(t_pipex *pipex)
{
	int	x;

	x = 0;
	if (!pipex)
		return ;
	if (pipex->pids)
		free (pipex->pids);
	if (pipex->paths)
	{
		x = 0;
		while (pipex->paths[x] != NULL)
			free (pipex->paths[x++]);
		free (pipex->paths);
	}
	if (pipex->file_in >= 0)
		close(pipex->file_in);
	if (pipex->file_out >= 0)
		close(pipex->file_out);
	if (pipex->prev_in >= 0)
		close(pipex->prev_in);
	free(pipex);
}

void	ft_error(char *s, t_pipex *pipex)
{
	ft_putendl_fd(s, 2);
	ft_clean_pipex(pipex);
	exit(1);
}
