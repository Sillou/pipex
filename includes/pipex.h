/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alubrano <alubrano@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:34:33 by alubrano          #+#    #+#             */
/*   Updated: 2026/01/09 15:44:02 by alubrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "libft.h"
#include <unistd.h>
#include <sys/types.h> // pid_t pipe struct ID parents
#include <stdio.h> // perror
#include <fcntl.h> // open

/*----------------pipex--------------*/

int	main(int agc, char **argv, char **envp);


#endif