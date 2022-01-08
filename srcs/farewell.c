/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   farewell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguilar <faguilar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 11:14:35 by faguilar          #+#    #+#             */
/*   Updated: 2022/01/08 13:01:49 by faguilar         ###   ########.fr       */
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

static void	white_std_error(int code)
{
	char *str_error;;
	
	str_error = strerror(code);
	ft_putstr_fd(str_error, 2);
	ft_putstr_fd("\n", 2);
	free_str(str_error);
}

void	farewell(int code, char **path, t_cmd *cmd1, t_cmd *cmd2)
{
	if (code == -1)
	{
		ft_putstr_fd("Error - Invalid number of arguments.\
		\nusage: ./pipex <infile> \"cmd1\" \"cmd2\" <outfile>.\n", 1);
	}
	if (code == ENOENT)
		ft_putstr_fd(strerror(code), 2);
	if (code == 0)
		free_all(path, cmd1, cmd2);
	white_std_error(code);
	exit (code);
}