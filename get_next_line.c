/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejung <hyejung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 19:41:15 by hyejung           #+#    #+#             */
/*   Updated: 2021/02/01 17:11:43 by hyejung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_num(char *back)
{
	int	num;

	num = 0;
	while (back[num])
	{
		if (back[num] == '\n')
			return (num);
		num++;
	}
	return (-1);
}

int	gnl_split(char **line, char **back)
{
	char	*tmp;
	int		num;
	int		back_len;

	num = gnl_num(*back);
	(*back)[num] = '\0';
	*line = ft_strdup(*back);
	back_len = ft_strlen(*back + num + 1);
	if (back_len == 0)
	{
		free(*back);
		*back = 0;
		return (1);
	}
	tmp = ft_strdup(*back + num + 1);
	free(*back);
	*back = ft_strdup(tmp);
	free(tmp);
	return (1);
}

int	gnl_rt(char **line, char **back)
{
	if (*back && (gnl_num(*back) >= 0))
		return (gnl_split(line, back));
	else if (*back)
	{
		*line = *back;
		*back = 0;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*back[OPEN_MAX];
	char		buf[BUFFER_SIZE + 1];
	char		*tmp;
	int			num;
	int			idx;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (back[fd] == NULL)
		back[fd] = ft_strdup("");
	while ((num = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[num] = '\0';
		tmp = ft_strjoin(back[fd], buf);
		free(back[fd]);
		back[fd] = ft_strdup(tmp);
		free(tmp);
		if ((idx = gnl_num(back[fd])) >= 0)
			return (gnl_split(line, &back[fd]));
	}
	if (num < 0)
		return (-1);
	return (gnl_rt(line, &back[fd]));
}
