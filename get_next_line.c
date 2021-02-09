/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejung <hyejung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 19:41:15 by hyejung           #+#    #+#             */
/*   Updated: 2021/02/04 00:11:53 by hyejung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int     gnl_num(char *back, int n)
{
    int     i;
    
    i = 0;
    while (back[i])
    {
        if (back[i] == n)
            return (i);
        i++;
    }
    return (-1);
}

int    gnl_new(char **line, char **back)
{
    char    *tmp;
    int     i;
    int     idx;
    size_t  size;
    
    if (*back != 0 && (idx = gnl_num(*back, '\n')) >= 0)
    {
        (*back)[idx] = '\0';
        if (!(*line = ft_strdup(*back)))
            return (-1);
        
        if ((size = ft_strlen(*back + idx + 1)) > 0)
            tmp = ft_strdup(*back + idx + 1);
        else
        {
            free(*back);
            *back = 0;
            return (1);
        }
        free(*back);
        if (!(*back = ft_strdup(tmp)))
            return (-1);
        free(tmp);
    }
    else
    {
        i = ((*back == 0) ? 0 : 1);
        if (!(*line = ((i == 1) ? ft_strdup(*back) : ft_strdup(""))))
            return (-1);
        free(*back);
        *back = NULL;
        return (0);
    }
    return (1);
}

int    get_next_line(int fd, char **line)
{
    static char    *back[OPEN_MAX];
    char        buf[BUFFER_SIZE + 1];
    char        *tmp;
    long        num;

    if (fd < 0 || fd > OPEN_MAX || *line == NULL || BUFFER_SIZE < 1)
        return (-1);
    while ((num = read(fd, buf, BUFFER_SIZE)) > 0)
    {
        buf[num] = '\0';
        if (back[fd] == NULL)
            tmp = ft_strdup(buf);
        else
            tmp = ft_strjoin(back[fd], buf);
        if (tmp == NULL)
            return (-1);
        free(back[fd]);
        back[fd] = ft_strdup(tmp);
        free(tmp);
    }
    return (gnl_new(line, &back[fd]));
}


#include <stdio.h>
#include <errno.h>
#include <string.h>
int main()
{
    char *new;
    char *new2;

    int fd;
    int fd2;
    int temp;
    int temp2;
	int i;
    
    
	i = 1;
    fd = open("./default_line.txt.output", O_RDONLY);
    fd2 = open("./65_line", O_RDONLY);
    
    
    new = (char*)malloc(sizeof(char) * 100);
    new2 = (char*)malloc(sizeof(char) * 100);
    if (!new || !new2)
        return (printf("noline \n"));
    while ((temp = get_next_line(fd, &new)) > 0)
    {
        printf("%d:%s\n",temp, new);
		i++;
    }
    printf("%d:%s.\n",temp, new);

	printf("--------------------\n");

   while ((temp2 = get_next_line(fd2, &new2)) > 0)
    {
        printf("%d:%s \n",temp2, new2);
		i++;
    }
    printf("%d:%s\n",temp2, new2);
}

