/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:59:44 by rugrigor          #+#    #+#             */
/*   Updated: 2023/11/21 16:46:44 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*strn(char *ptr)
{
	int		i;
	char	*p;

	i = 0;
	while (ptr && ptr[i] && ptr[i] != '\n')
		i++;
	p = ft_substr(ptr, 0, i + 1);
	return (p);
}

char	*strn2(char *ptr)
{
	int		i;
	char	*p;

	i = 0;
	while (ptr && ptr[i] && ptr[i] != '\n')
		i++;
	p = ft_substr(ptr, i + 1, ft_strlen(ptr) - i + 1);
	free(ptr);
	ptr = ft_strdup(p);
	free(p);
	p = (NULL);
	return (ptr);
}

static char	*go_go(char *buff, int fd, char *str)
{
	int		i;
	char	*p;

	if (ft_strchr(str, '\n'))
		return (str);
	i = read(fd, buff, BUFFER_SIZE);
	while (i > 0)
	{
		buff[i] = '\0';
		if (!str)
			str = ft_strdup("");
		p = ft_strdup(str);
		free(str);
		str = ft_strjoin(p, buff);
		free(p);
		p = (NULL);
		if (ft_strchr(str, '\n'))
			break ;
		i = read(fd, buff, BUFFER_SIZE);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*ptr;
	char		*buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	str = go_go(buff, fd, str);
	ptr = strn(str);
	free(buff);
	buff = NULL;
	if (!str)
		return (NULL);
	str = strn2(str);
	if (*ptr == 0)
	{
		free(str);
		str = (NULL);
		free(ptr);
		ptr = (NULL);
		return (NULL);
	}
	return (ptr);
}
