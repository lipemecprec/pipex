/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguilar <faguilar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 13:34:16 by faguilar          #+#    #+#             */
/*   Updated: 2022/04/20 16:41:23 by faguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define WRONG_ARG_NO	450
# define READ_END		0
# define WRITE_END		1
# define PERM_0664		436

# define STDIN	0
# define STDOUT	1
# define STDERR	2

# define OP_NOT_ALLOWED	1
# define ERR_NO_FILE	2
# define ERR_NO_JOB		127

# define ERR_MSG_ARG	"Wrong usage. Invalid number of arguments.\n"
# define ERR_MSG_FILE	": invalid file.\n"
# define ERR_MSG_PIPE	"Error on initializing pipe.\n"
# define ERR_MSG_FORK	"Error on forking.\n"
# define ERR_MSG_CMD	": command not found.\n"

// libft
# include "../libft/libft.h"
// printf
# include "../ft_printf/include/ft_printf.h"
// lib for: open
# include <fcntl.h>
// lib for: access, unlink, close, read, pipe, dup, dup2, execve, fork
# include <unistd.h> 
// lib for: malloc, free, exit
# include <stdlib.h>
// libs for: waitpid, wait, fork
# include <sys/types.h>
# include <sys/wait.h>
// libs for: perror, strerror
# include "stdio.h"
# include "string.h"
# include "errno.h"

typedef struct s_cmd
{
	int		infile;
	int		outfile;
	char	*path;
	char	**cmd_array;
}			t_cmd;

typedef struct s_pipex
{
	t_cmd	cmd1;
	t_cmd	cmd2;
	char	**path;
	int		exec_status;
}			t_pipex;

void	terminate(int code, char **path, t_cmd *cmd1, t_cmd *cmd2);

#endif