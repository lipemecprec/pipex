/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguilar <faguilar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 13:16:22 by faguilar          #+#    #+#             */
/*   Updated: 2021/11/23 22:34:29 by faguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	remmsub;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = 0;
	while (s[s_len] != '\0')
		s_len++;
	remmsub = s_len - start;
	if (start <= s_len)
	{
		if (remmsub > len)
			sub = (char *)malloc(sizeof(char) * len + 1);
		else
			sub = (char *)malloc(sizeof(char) * remmsub + 1);
		if (!sub)
			return (NULL);
		ft_strlcpy(sub, &s[start], len + 1);
	}
	else
		return (ft_strdup(""));
	return (sub);
}
