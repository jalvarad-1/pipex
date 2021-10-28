/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 12:00:34 by jalvarad          #+#    #+#             */
/*   Updated: 2021/09/25 11:53:05 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (src == dst)
		return (dst);
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	a;
	size_t	b;

	if (!*(needle))
		return ((char *)haystack);
	if (!*(haystack))
		return (0);
	a = 0;
	while (haystack[a] != 0)
	{
		b = 0;
		while (needle[b] == haystack[a + b] && b < len)
		{
			if (needle[b + 1] == 0 && a + b < len)
				return ((char *)haystack + a);
			b++;
		}
		a++;
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		n;
	int		a;
	int		len;
	char	*aux_s1;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	n = 0;
	a = 0;
	aux_s1 = malloc(sizeof(char) * (len + 1));
	if (!aux_s1)
		return (0);
	ft_memcpy(aux_s1, s1, ft_strlen(s1) + 1);
	while (aux_s1[a] != '\0')
		a++;
	while (s2[n] != '\0')
	{
		aux_s1[a + n] = s2[n];
		n++;
	}
	aux_s1[a + n] = '\0';
	return (aux_s1);
}

void	del_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
