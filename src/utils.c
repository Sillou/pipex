/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alubrano <alubrano@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 17:37:28 by alubrano          #+#    #+#             */
/*   Updated: 2026/01/16 18:25:42 by alubrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exec(t_pipex *pipex, char *argv)
{
	char	**t_cmd;
	char	*cmd_path;
	char	*temp;
	int		i;

	t_cmd = ft_split(argv, ' ');
	if (!t_cmd || !t_cmd[0])
		ft_error("Path split Error", pipex);
	i = 0;
	while (pipex->paths[i])
	{
		temp = ft_strjoin(pipex->paths[i], "/");
		cmd_path = ft_strjoin(temp, t_cmd[0]);
		free(temp);
		if (access(argv, X_OK) == 0)
			execve(argv, t_cmd, pipex->envp);
		if (access(cmd_path, X_OK) == 0)
			execve(cmd_path, t_cmd, pipex->envp);
		free(cmd_path);
		i++;
	}
	ft_putendl_fd("CMD not found", 2);
	ft_free_cmd(t_cmd);
	ft_clean_pipex(pipex);
	exit(1);
}

void	ft_get_path(t_pipex *pipex)
{
	int		i;
	char	*line;

	line = NULL;
	i = 0;
	while (pipex->envp[i] != NULL)
	{
		if (ft_strnstr(pipex->envp[i], "PATH=", 5) == pipex->envp[i])
		{
			line = pipex->envp[i] + 5;
			break ;
		}
		i++;
	}
	if (!line)
		ft_error("Path not found", pipex);
	pipex->paths = ft_split(line, ':');
	if (!pipex->paths)
		ft_error("Path split Error", pipex);
}

void	ft_free_cmd(char **t_cmd)
{
	int	x;

	x = 0;
	while (t_cmd[x])
		free(t_cmd[x++]);
	free(t_cmd);
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
