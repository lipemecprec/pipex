/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguilar <faguilar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 13:33:57 by faguilar          #+#    #+#             */
/*   Updated: 2022/04/19 13:25:31 by faguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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
			free(try);
			break ;
		}
		free(try);
		path++;
	}
}

void	set_cmds(char *argv[], char **path, t_cmd *cmd1, t_cmd *cmd2)
{
	char	*temp;

	if (!argv[2])
		terminate(139, NULL, NULL, NULL);
	else
		new_cmd(cmd1, argv[2], path);
	if (!cmd1->path)
	{
		temp = ft_strjoin(*cmd1->cmd_array, ERR_MSG_CMD);
		write(STDERR, temp, ft_strlen(temp) + 1);
		free(temp);
	}
	new_cmd(cmd2, argv[3], path);
	if (!cmd2->path)
	{
		temp = ft_strjoin(*cmd2->cmd_array, ERR_MSG_CMD);
		write(STDERR, temp, ft_strlen(temp) + 1);
		free(temp);
	}
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
			break ;
		}		
		*envp++;
	}
	return (path);
}

void	set_files(char *argv[], t_cmd *cmd1, t_cmd *cmd2)
{
	cmd2->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (access(argv[1], F_OK) != 0)
		terminate(OP_NOT_ALLOWED, NULL, cmd1, cmd2);
	cmd1->infile = open(argv[1], O_RDONLY);
	if (cmd1->infile == -1)
		cmd1->infile = STDIN;
}

// Desemperra:
// Para o bônus, o processo pai direciona o STDIN para o pipe, e faz o fork
// Dentro de um laço, enquanto houver argv, cada filho manda o STDOUT para o próximo processo
// Depois de executar todos os filhos, o processo pai printa a saída.
// 
// 1 pipe para cada interprocesso.
// Matar todos os filhos
// estudar wait para pegar os erros dos processos.
int	main(int argc, char *argv[], char *envp[])
{
	int		pipefd[2];
	int		pid;
	int		pid2;
	t_pipex	data;

	if (argc != 5 || !argv[2] || !argv[3] )
		terminate(WRONG_ARG_NO, NULL, NULL, NULL);
	data.path = get_envpath(envp);
	set_files(argv, &data.cmd1, &data.cmd2);
	set_cmds(argv, data.path, &data.cmd1, &data.cmd2);
	dup2(data.cmd1.infile, STDIN);
	// perror("MAIN > ");
	dup2(data.cmd2.outfile, STDOUT);
	if (pipe(pipefd) == -1)
		terminate(errno, data.path, &data.cmd1, &data.cmd2);
	pid = fork();
	if (pid == -1)
		terminate(errno, data.path, &data.cmd1, &data.cmd2);
	if (pid == 0)
	{
		dup2(pipefd[WRITE_END], STDOUT);
		close(pipefd[READ_END]);
		close(pipefd[WRITE_END]);
		if (execve(data.cmd1.path, data.cmd1.cmd_array, envp) == -1)
			terminate(errno, data.path, &data.cmd1, &data.cmd2);
		// printf("pid = 0 > err code: %d | err msg %s", errno, strerror(errno));
	}
	pid2 = fork();
	if (pid2 == -1)
		return (3);
	if (pid2 == 0)
	{
		dup2(pipefd[READ_END], STDIN);
		close(pipefd[READ_END]);
		close(pipefd[WRITE_END]);
		if (execve(data.cmd2.path, data.cmd2.cmd_array, envp) == -1)
			terminate(errno, data.path, &data.cmd1, &data.cmd2);
		// printf("pid2 = 0 > err code: %d | err msg %s", errno, strerror(errno));
	}
	close(pipefd[READ_END]);
	close(pipefd[WRITE_END]);
	waitpid(pid, NULL, 0);
	if (!data.cmd2.path)
		terminate(ERR_NO_JOB, data.path, &data.cmd1, &data.cmd2);
	terminate(EXIT_SUCCESS, data.path, &data.cmd1, &data.cmd2);
	return (0);
}
