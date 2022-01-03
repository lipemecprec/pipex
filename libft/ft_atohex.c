/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atohex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguilar <faguilar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 23:58:18 by faguilar          #+#    #+#             */
/*   Updated: 2021/12/27 16:10:59 by faguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ctohex(char c)
{
	if (('0' <= c) && (c <= '9'))
		return (c - '0');
	else if (('A' <= c) && (c <= 'F'))
		return (10 + c - 'A');
	else if (('a' <= c) && (c <= 'f'))
		return (10 + c - 'a');
	return (0);
}

int	ft_atohex(const char *num_str)
{
	char	*hex_str;
	int		i;
	int		num_int;
	int		base;

	hex_str = ft_strchr(num_str, 'x');
	if (hex_str == NULL)
		hex_str = ft_strchr(num_str, 'X');
	if (hex_str == NULL)
		return (-1);
	num_int = 0;
	base = 1;
	i = ft_strlen(hex_str) - 1;
	while (i > 0)
	{
		num_int = num_int + ctohex(hex_str[i]) * base;
		base *= 16;
		i--;
	}
	return (num_int);
}
