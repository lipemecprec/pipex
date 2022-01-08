/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   farewell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguilar <faguilar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 11:14:35 by faguilar          #+#    #+#             */
/*   Updated: 2022/01/08 20:14:32 by faguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

static void	free_all(char **path, t_cmd *cmd1, t_cmd *cmd2)
{
	free_str_arr(path);
	free_str_arr(cmd1->cmd_array);
	free_str_arr(cmd2->cmd_array);
	free_str(cmd1->path);
	free_str(cmd2->path);
}

void	farewell(int code, char **path, t_cmd *cmd1, t_cmd *cmd2)
{
	if (code == EXIT_SUCCESS)
		free_all(path, cmd1, cmd2);
	else if (code == WRONG_ARG_NO)
	{
		ft_putstr_fd("Error - Invalid number of arguments.\
		\nusage: ./pipex <infile> \"cmd1\" \"cmd2\" <outfile>.\n", 1);
		ft_putstr_fd("Wrong number of arguments.\n", 2);
	}
	else if (code == ENOENT)
		ft_putstr_fd(strerror(code), 2);
	else if (code == EACCES)
		ft_putstr_fd(strerror(code), 2);
	// white_std_error(code);
	ft_putstr_fd("\n", 2);
	exit (code);
}
