/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alubrano <alubrano@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:34:33 by alubrano          #+#    #+#             */
/*   Updated: 2026/01/12 09:16:46 by alubrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "libft.h"
#include <unistd.h>
#include <sys/types.h> // pid_t pipe struct ID parents
#include <stdio.h> // perror
#include <fcntl.h> // open
#include <sys/wait.h> // for waipid

typedef struct s_pipex
{
	int		file_in;
	int		file_out;
	int 	prev_in;
	pid_t	*pids;
	int		n_cmd;
	int		i;
	char	**envp;
	char	**paths;
}	t_pipex;


/*----------------pipex--------------*/

int	main(int agc, char **argv, char **envp);


#endif