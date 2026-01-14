/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alubrano <alubrano@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:34:33 by alubrano          #+#    #+#             */
/*   Updated: 2026/01/14 16:57:14 by alubrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/types.h> // pid_t pipe struct ID parents
# include <stdio.h> // perror
# include <fcntl.h> // open
# include <sys/wait.h> // for waipid
# include "libft.h"

typedef struct s_pipex
{
	int		file_in;
	int		file_out;
	int		prev_in;
	pid_t	*pids;
	int		n_cmd;
	int		i;
	char	**envp;
	char	**paths;
}	t_pipex;

/*----------------pipex--------------*/

int		main(int agc, char **argv, char **envp);
t_pipex	*ft_ini_pipex(int argc, char **argv, char **envp);
int		ft_open(char *argv, int z, t_pipex	*pipex);
pid_t	ft_cmd_last(t_pipex *pipex, char *argv);
pid_t	ft_cmd(t_pipex *pipex, char *argv);

/*----------------utils--------------*/

void	ft_error(char *s, t_pipex *pipex);
void	ft_clean_pipex(t_pipex *pipex);
void	ft_free_cmd(char **t_cmd);
void	ft_get_path(t_pipex *pipex);
void	ft_exec(t_pipex *pipex, char *argv);

#endif