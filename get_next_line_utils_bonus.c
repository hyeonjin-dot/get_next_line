/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejung <hyejung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 18:26:51 by hyejung           #+#    #+#             */
/*   Updated: 2021/02/13 18:26:59 by hyejung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		ft_strlen(const char *str)
{
	int		i;

	i = 0;
	while (*str != '\0')
	{
		i++;
		str++;
	}
	return (i);
}

char	*ft_strdup(const char *str)
{
	size_t	str_len;
	size_t	i;
	char	*new;

	i = 0;
	str_len = ft_strlen(str);
	new = (char*)malloc(sizeof(char) * (str_len + 1));
	if (new == NULL)
		return (0);
	while (i < str_len)
	{
		*(new + i) = *(str + i);
		i++;
	}
	*(new + i) = '\0';
	return (new);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		*(char*)(dest + i) = *(char*)(src + i);
		i++;
	}
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		s1_len;
	int		s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (!(new = (char*)malloc(sizeof(char) * (s1_len + s2_len + 1))))
		return (0);
	ft_memcpy(new, s1, s1_len);
	ft_memcpy(new + s1_len, s2, s2_len);
	*(new + s1_len + s2_len) = '\0';
	return (new);
}
