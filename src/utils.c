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