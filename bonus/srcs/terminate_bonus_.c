/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguilar <faguilar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 11:14:35 by faguilar          #+#    #+#             */
/*   Updated: 2022/04/19 11:06:24 by faguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static void	free_str(char *str)
{
	free(str);
	str = NULL;
}

static void	free_str_arr(char **arr)
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

static void	free_all(t_pipex *data)
{
	free_str_arr(data->cmd1.cmd_array);
	free_str_arr(data->cmd2.cmd_array);
	free_str(data->cmd1.path);
	free_str(data->cmd2.path);
	free_str_arr(data->env_path);
}

void	terminate(int exit_code, t_pipex *data)
{
	if (exit_code == EXIT_SUCCESS)
		free_all(data);
	else if (exit_code == WRONG_ARG_NO)
	{
		ft_putstr_fd("Error - Invalid number of arguments.\
		\nusage: ./pipex <infile> \"cmd1\" \"cmd2\" <outfile>.\n", 1);
		write(STDERR, ERR_MSG_ARG, ft_strlen(ERR_MSG_ARG));
	}
	exit (exit_code);
}
