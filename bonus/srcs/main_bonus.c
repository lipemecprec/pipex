/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguilar <faguilar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 13:21:37 by faguilar          #+#    #+#             */
/*   Updated: 2022/04/23 00:17:28 by faguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	write_args(int argc, char **argv, char **envp)
{
	#include <string.h> 
	int i = 0;
	char arg_num[2];

	arg_num[1] = 0;
	write(1, "----\n", 6);
	write(1, "argv > ", 6);
	while (i < argc)
	{
		arg_num[0] = '0' + i;
		write(1, "\t", 2);
		write(1, arg_num, 2);
		write(1, ">", 2);
		write(1, argv[i], strlen(argv[i]));
		if(!argv[i][0])
			write(1, "VAZIO", 6);
		i++;
	}
	write(1, "\n", 2);
	write(1, "----\n", 6);
}

void	new_cmd(t_cmd *cmd, char *cmd_str, char **env_path)
{
	char	*try;
	char	*temp;

	if(cmd_str)
	{
		cmd->cmd_array = ft_split(cmd_str, ' ');
		cmd->path = NULL;
		while (*env_path)
		{
			temp = ft_strjoin(*env_path, "/");
			try = ft_strjoin(temp, *cmd->cmd_array);
			free(temp);
			if (access(try, X_OK) == 0)
			{
				cmd->path = ft_strdup(try);
				free(try);
				break ;
			}
			free(try);
			env_path++;
		}
	}
}

char	*get_cmd_path(char *cmd_str, char **env_path)
{
	char	*try;
	char	*temp;
	char	**cmd_arr;

	if(cmd_str)
	{
		cmd_arr = ft_split(cmd_str, ' ');
		while (*env_path)
		{
			temp = ft_strjoin(*env_path, "/");
			try = ft_strjoin(temp, *cmd_arr);
			free(temp);
			if (access(try, X_OK) == 0)
			{
				free(cmd_arr);
				return (try);
			}
			free(try);
			env_path++;
		}
	}
	return (NULL);
}

char	**get_cmd_args(char *cmd_str)
{
	char	**cmd_args;

	if(ft_strlen(cmd_str)!= 0)
	{
		cmd_args = ft_split(cmd_str, ' ');
		return (cmd_args);
	}
	return (NULL);
}

void	set_cmds(char *argv[], t_pipex *data)
{
	char *temp;
	
	if (argv[2][0])
		new_cmd(&data->cmd1, argv[2], data->env_path);
	if (argv[3][0])
		new_cmd(&data->cmd2, argv[3], data->env_path);
}

char	**get_envpath(char *envp[])
{
	char	**env_path;
	char	*temp;

	env_path = NULL;
	while (*envp)
	{
		if (ft_strnstr(*envp, "PATH=", 5))
		{
			temp = ft_strrchr(*envp, '=') + 1;
			env_path = ft_split(temp, ':');
			break ;
		}		
		*envp++;
	}
	return (env_path);
}

void	set_infile(char *argv[], t_pipex *data)
{
	data->infile = open(argv[1], O_RDONLY);
	if (data->infile == -1)
		data->infile = STDIN;
	dup2(data->infile, STDIN);
}

void	set_outfile(char *argv[], t_pipex *data)
{
	int	last;

	last = data->argc - 1;
	data->outfile = open(argv[last], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (access(argv[1], F_OK) != 0)
		terminate(OP_NOT_ALLOWED, data);
	dup2(data->outfile, STDOUT);
}

void	read_args(t_pipex *data, int argc, char *argv[], char *envp[])
{
	write_args(argc, argv, envp);
	// if (argc != 5)
	// 	terminate(WRONG_ARG_NO, data);
	data->argc = argc;
	data->env_path = get_envpath(envp);
	set_infile(argv, data);
	set_outfile(argv, data);
	set_cmds(argv, data);
}

void	run_process(t_pipex *data, int *pipe, char *cmd_str, char *envp[])
{
	char	*cmd_path;
	char	**cmd_args;

	cmd_path = get_cmd_path(cmd_str, data->env_path);
	cmd_args = get_cmd_args(cmd_str);
	dup2(pipe[WRITE_END], STDOUT);
	close(pipe[READ_END]);
	close(pipe[WRITE_END]);
	if (execve(cmd_path, cmd_args, envp) == -1)
		terminate(errno, data);
}

void	create_pipes(t_pipex *data)
{
	int	i;
	int	pipes_qty;

	pipes_qty = data->argc - 1;
	i = 1;
	data->pipes = (int **)malloc(pipes_qty * sizeof(int *));
	while (i < pipes_qty)
	{
		data->pipes[i] = (int *)malloc(2 * sizeof(int));
		if (pipe(data->pipes[i]) == -1)
			terminate(errno, NULL); // TODO: create destroy pipes funcion;
		printf("PIPE #%d > fd[0] = %d\t fd[1] = %d\n", i, data->pipes[i][0], data->pipes[i][1]);
		i++;
	}
}

// Desemperra:
// Para o bônus, o processo pai direciona o STDIN para o pipe, e faz o fork
// Dentro de um laço, enquanto houver argv, cada filho manda o STDOUT para o próximo processo
// Depois de executar todos os filhos, o processo pai printa a saída.

// 1 pipe para cada interprocesso.
// Matar todos os filhos
// estudar wait para pegar os erros dos processos.
int	main(int argc, char *argv[], char *envp[])
{
	int		pipefd[2];
	int		pid;
	int		pid2;
	t_pipex	data;
	int		wstatus;

	read_args(&data, argc, argv, envp);
	// create_pipes(&data);
	if (pipe(pipefd) == -1)
		terminate(errno, &data);
	pid = fork();
	if (pid == -1)
		terminate(errno, &data);
	if (pid == 0)
	{
		run_process(&data, pipefd, argv[2], envp);
		// dup2(pipefd[WRITE_END], STDOUT);
		// close(pipefd[READ_END]);
		// close(pipefd[WRITE_END]);
		// if (execve(data.cmd1.path, get_cmd_args(argv[2]), envp) == -1)
		// 	terminate(errno, &data);
	}
	pid2 = fork();
	if (pid2 == -1)
		return (3);
	if (pid2 == 0)
	{
		dup2(pipefd[READ_END], STDIN);
		close(pipefd[READ_END]);
		close(pipefd[WRITE_END]);
		if (execve(data.cmd2.path, get_cmd_args(argv[3]), envp) == -1)
			terminate(errno, &data);
	}
	close(pipefd[READ_END]);
	close(pipefd[WRITE_END]);
	waitpid(pid, NULL, 0);
	if (!data.cmd2.path)
		terminate(ERR_NO_JOB, &data);
	terminate(EXIT_SUCCESS, &data);
	return (0);
}
