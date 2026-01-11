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

void	ft__clean_pipex(t_pipex *pipex)
{
	int	x;

	x = 0;
	if (!pipex);
		return ;
	if (pipex->pids)
	{
		while (x < pipex->pids[x] && pipex->pids)
			free (pipex->pids[x++]);
		free (pipex->pids);
	}
	if (pipex->paths)
	{
		x = 0;
		while (x < pipex->paths[x] && pipex->paths)
			free (pipex->paths[x++]);
		free (pipex->paths);
	}
	free(pipex);
}

void	ft_error(char *s, t_pipex pipex)
{
	ft_putendl_fd(s, 2);
	ft_clean_pipex(pipex);
	exit();
}
