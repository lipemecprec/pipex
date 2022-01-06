/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguilar <faguilar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 13:33:57 by faguilar          #+#    #+#             */
/*   Updated: 2022/01/06 16:54:06 by faguilar         ###   ########.fr       */
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

t_cmd	new_cmd(char *cmd_str, char **path)
{
	t_cmd	cmd;
	char	*try;
	char	*temp;

	cmd.cmd_array = ft_split(cmd_str, ' ');
	while (*path)
	{
		temp = ft_strjoin(*path, "/");
		try = ft_strjoin(temp, *cmd.cmd_array);
		free(temp);
		if (access(try, X_OK) == 0)
		{
			cmd.path = try;
			free(try);
			break;
		}
		free(try);
		path++;
	}
	// int	i = 0;
	// while (cmd.cmd_array[i])
	// {
	// 	free(cmd.cmd_array[i]);
	// 	i++;
	// }
	// free(cmd.cmd_array);
	return (cmd);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
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
			printf("%s", temp);
			path = ft_split(temp, ':');
			break;
		}
		*envp++;
	}
	return (path);
}

void	set_cmd(char *argv[], char **path, t_cmd *cmd1, t_cmd *cmd2)
{
	*cmd1 = new_cmd(argv[2], path);
	*cmd2 = new_cmd(argv[3], path);
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
	free_arr(path);
	free_arr(cmd1.cmd_array);
	free_arr(cmd2.cmd_array);
	if (pipe(pipefd) == -1)
		return 1;

	pid = fork();
	if (pid == -1)
		return (2);

	if (pid == 0)
	{
		char *ping[] = {"/usr/bin/ping", "-c", "2", "google.com", NULL};
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execve("/usr/bin/ping", ping, NULL);
	}

	int pid2 = fork();

	if (pid2 == -1)
		return (3);

	if (pid2 == 0)
	{
		char *grep[] = {"/usr/bin/grep", "rtt",  NULL};
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execve("/usr/bin/grep", grep, NULL);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
