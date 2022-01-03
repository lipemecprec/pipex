/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguilar <faguilar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 13:34:16 by faguilar          #+#    #+#             */
/*   Updated: 2022/01/03 15:14:59 by faguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"

// lib for : open
# include <fcntl.h>
// lib for : access, unlink, close, read, pipe, dup, dup2, execve, fork
# include <unistd.h> 
// lib for : malloc, free, exit
# include <stdlib.h>
// libs for : waitpid, wait, fork
# include <sys/types.h>
# include <sys/wait.h>
#endif