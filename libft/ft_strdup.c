/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguilar <faguilar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 02:36:25 by faguilar          #+#    #+#             */
/*   Updated: 2021/11/23 22:34:07 by faguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dup;

	if (!s)
		return (NULL);
	len = 0;
	while (s[len] != '\0')
		len++;
	dup = (char *)malloc(sizeof(char) * len + 1);
	if (dup == NULL)
		return (NULL);
	ft_strlcpy(dup, s, len + 1);
	return (dup);
}
