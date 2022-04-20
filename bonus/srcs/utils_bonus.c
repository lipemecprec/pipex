/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguilar <faguilar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 18:07:33 by faguilar          #+#    #+#             */
/*   Updated: 2022/04/02 23:41:16 by faguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	*mgrant(int size)
{
	void	*memory_alloc;

	memory_alloc = malloc(size);
	if (!memory_alloc)
	{
		terminate(ENOMEM, NULL, NULL, NULL);
	}
	else
		return (memory_alloc);
	return (NULL);
}

void	set_free(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

int	open_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY, 1);
	if (fd == -1)
		terminate(ENOMEM, NULL, NULL, NULL);
	return (fd);
}
