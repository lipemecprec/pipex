/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguilar <faguilar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 13:33:57 by faguilar          #+#    #+#             */
/*   Updated: 2022/01/05 20:08:30 by faguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include "stdio.h"

// typedef struct s_cmd
// {
// 	char *path;
// 	char **cmd_array;
// } 				t_cmd;

// t_cmd	new_cmd(char *cmd_str, char **path)
// {
// 	t_cmd	cmd;
// 	char	*try;
// 	char	**cmd_arr;

// 	ft_putstr_fd(cmd_str, 1);
// 	ft_putstr_fd("\n", 1);
// 	cmd_arr = ft_split(cmd_str, ' ');
	
// 	while (*path)
// 	{
// 		try = ft_strjoin(*path, "/");
// 		try = ft_strjoin(try, cmd_arr[0]);
// 		ft_putstr_fd(try, 1);
// 		ft_putstr_fd("\n", 1);
// 		// try = "/usr/bin/ping";
// 		if (access(try, X_OK) == 0)
// 			break;
// 		path++;
// 	}
// 	cmd.path = try;
// 	return (cmd);
// }

char	**get_envpath(char *envp[])
{
	char	**path;

	path = NULL;
	while (*envp)
	{
		if (ft_strnstr(*envp, "PATH", 5))
			path = ft_split(*envp, ':');
		*envp++;
	}
	path[0] = ft_strtrim(path[0], "PATH=");
	return (path);
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
	// t_cmd	cmd1;

	path = get_envpath(envp);
	// cmd1 = new_cmd(argv[2], path);
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
