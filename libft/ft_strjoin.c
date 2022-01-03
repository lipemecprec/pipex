/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguilar <faguilar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 14:25:03 by faguilar          #+#    #+#             */
/*   Updated: 2021/11/23 22:34:19 by faguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	s1len;
	size_t	s2len;

	s1len = 0;
	while (s1[s1len] != '\0')
		s1len++;
	s2len = 0;
	while (s2[s2len] != '\0')
		s2len++;
	join = (char *)malloc(sizeof(char) * (s1len + s2len + 1));
	if (!join)
		return (NULL);
	ft_strlcpy(&join[0], s1, s1len + 1);
	ft_strlcpy(&join[s1len], s2, s2len + 1);
	return (join);
}
