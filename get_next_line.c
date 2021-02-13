/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejung <hyejung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 19:41:15 by hyejung           #+#    #+#             */
/*   Updated: 2021/02/13 18:10:25 by hyejung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		gnl_num(char *back, int n)
{
	int		i;

	i = 0;
	while (back[i])
	{
		if (back[i] == n)
			return (i);
		i++;
	}
	return (-1);
}

int		gnl_new(char **line, char **back)
{
	char	*tmp;
	int		idx;

	if (*back && (idx = gnl_num(*back, '\n')) >= 0)
	{
		(*back)[idx] = '\0';
		*line = ft_strdup(*back);
		tmp = ft_strdup(*back + idx + 1);
		free(*back);
		*back = ft_strdup(tmp);
		free(tmp);
	}
	else
	{
		if (*back)
		{
			*line = ft_strdup(*back);
			free(*back);
			*back = 0;
		}
		else
			*line = ft_strdup("");
		return (0);
	}
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char	*back[OPEN_MAX];
	char		buf[BUFFER_SIZE + 1];
	char		*tmp;
	long		num;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	while ((num = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[num] = '\0';
		tmp = 0;
		if (back[fd] == NULL)
			back[fd] = ft_strdup(buf);
		else
		{
			tmp = ft_strjoin(back[fd], buf);
			free(back[fd]);
			back[fd] = tmp;
		}
		if (gnl_num(back[fd], '\n') >= 0)
			return (gnl_new(line, &back[fd]));
	}
	if (num < 0)
		return (-1);
	return (gnl_new(line, &back[fd]));
}
