/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguilar <faguilar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 13:33:57 by faguilar          #+#    #+#             */
/*   Updated: 2022/01/08 08:43:35 by faguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include "stdio.h"

typedef struct s_cmd
{
	char *infile;
	char *outfile;
	char *path;
	char **cmd_array;
} 				t_cmd;

void	new_cmd(t_cmd *cmd, char *cmd_str, char **path)
{
	char	*try;
	char	*temp;

	cmd->cmd_array = ft_split(cmd_str, ' ');
	cmd->path = NULL;
	while (*path)
	{
		temp = ft_strjoin(*path, "/");
		try = ft_strjoin(temp, *cmd->cmd_array);
		free(temp);
		if (access(try, X_OK) == 0)
		{
			cmd->path = ft_strdup(try);
			break;
		}
		free(try);
		path++;
	}
	free(try);
}

void	free_str(char *str)
{
	free(str);
	str = NULL;
}

void	free_str_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free_str(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

void	free_all(char **path, t_cmd *cmd1, t_cmd *cmd2)
{
	free_str_arr(path);
	free_str_arr(cmd1->cmd_array);
	free_str_arr(cmd2->cmd_array);
	free_str(cmd1->path);
	free_str(cmd2->path);
}

char	**get_envpath(char *envp[])
{
	char	**path;
	char	*temp;

	path = NULL;
	while (*envp)
	{
		if (ft_strnstr(*envp, "PATH=", 5))
		{
			temp = ft_strrchr(*envp, '=') + 1;
			path = ft_split(temp, ':');
			break;
		}
		*envp++;
	}
	return (path);
}

void	farewell()
{
	exit (0);
}

void	set_cmd(char *argv[], char **path, t_cmd *cmd1, t_cmd *cmd2)
{
	int	fd;
	
	new_cmd(cmd1, argv[2], path);
	if(!cmd1->path)
		farewell();
	new_cmd(cmd2, argv[3], path);
	if(!cmd2->path)
		farewell();
	cmd1->infile = argv[1];
	fd = open(cmd1->infile, O_RDONLY);
	if (fd == -1)
		farewell();
	cmd2->outfile = argv[4];
	fd = open(cmd2->outfile, O_RDWR);
	if (fd == -1)
		farewell();
}

// ls -la /proc/$$/fd
// /pipex infile ``ls -l'' ``wc -l'' outfile
int main(int argc, char *argv[], char *envp[])
{
	int pipefd[2];
	int pid;
	char *infile;
	char **path;
	char *outfile;
	t_cmd	cmd1;
	t_cmd	cmd2;

	path = get_envpath(envp);
	set_cmd(argv, path, &cmd1, &cmd2);
	if (pipe(pipefd) == -1)
		return 1;

	pid = fork();
	if (pid == -1)
		return (2);

	if (pid == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execve(cmd1.path, cmd1.cmd_array, envp);
	}

	int pid2 = fork();

	if (pid2 == -1)
		return (3);

	if (pid2 == 0)
	{
		// int fd_out = open(cmd2.outfile, O_CREAT | O_RDWR, 0664);
		dup2(pipefd[0], STDIN_FILENO);
		// dup2(pipefd[1], fd_out);
		close(pipefd[0]);
		close(pipefd[1]);
		execve(cmd2.path, cmd2.cmd_array, envp);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	free_all(path, &cmd1, &cmd2);
	return (0);
}
