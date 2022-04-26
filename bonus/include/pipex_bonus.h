/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguilar <faguilar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 13:21:19 by faguilar          #+#    #+#             */
/*   Updated: 2022/04/26 10:57:43 by faguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
# include "../../libft/libft.h"
// libs for open
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
// lib for: access, unlink, close, read, pipe, dup, dup2, execve, fork
# include <unistd.h> 
// lib for: malloc, free, exit
# include <stdlib.h>
// libs for: waitpid, wait, fork
# include <sys/types.h>
# include <sys/wait.h>
// libs for: perror, strerror
# include <stdio.h>
# include <string.h>
# include <errno.h>

typedef struct s_cmd
{
	char	*path;
	char	**cmd_array;
}			t_cmd;

typedef struct s_pipex
{
	int		argc;
	int		infile;
	int		outfile;
	t_cmd	cmd1;
	t_cmd	cmd2;
	char	**env_path;
	int		exec_status;
	int		args_index;
	int		**pipes;
}			t_pipex;

void	terminate(int exit_code, t_pipex *data);

#endif