/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguilar <faguilar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 13:33:57 by faguilar          #+#    #+#             */
/*   Updated: 2022/01/03 17:39:12 by faguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include "stdio.h"

// /pipex infile ``ls -l'' ``wc -l'' outfile
int main(int argc, char *argv[])
{
	int fd[2];
	int pipex;
	int pid;
	char *infile;
	char *outfile;

	// int	i = 0;
	// while (i < argc + 1)
	// {
	// 	printf("arg[%d] = %s\n", i, argv[i]);
	// 	i++;
	// }

	pipex = pipe(fd);
	if (pipex == -1)
		return 1;

	pid = fork();
	if (pid == -1)
		return (2);
	
	if (pid == 0)
	{
		char *ping[] = {"/usr/bin/ping", "-c", "2", "google.com", NULL};
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve("/usr/bin/ping", ping, NULL);
	}

	int pid2 = fork();

	if (pid2 == -1)
		return (3);

	if (pid2 == 0)
	{
		char *grep[] = {"/usr/bin/grep", "rtt",  NULL};
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve("/usr/bin/grep", grep, NULL);
	}
	close(fd[0]);
	close(fd[1]);
	// wait(NULL);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
