/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:38:53 by rugrigor          #+#    #+#             */
/*   Updated: 2023/08/24 11:34:17 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*dol(char *str, char *ft, int n)
{
	char	*ft2;
	char	*str2;

	ft2 = NULL;
	str2 = ft_strtrim(str, "\n");
	if (ft == NULL)
		ft = (str2 + n);
	else
	{
		ft2 = ft_strjoin(ft, str2 + n);
		ft = ft2;
	}
	return (ft);
}

char	*dollar2(t_ms *ms, char *ptr, int n, char *ft)
{
	char	*str2;
	char	*str;
	int		fd;

	if (n < 2)
		return (NULL);
	ms->dol = ms->dol - 1;
	ptr[n - 1] = '\0';
	fd = open("cache", O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		if (ptr != 0 && ft_strncmp(ft_strjoin(ptr, "="),
				str, ft_strlen(ptr) + 1) == 0)
		{
			str2 = ft_strtrim(str, "\n");
			ft = (str2 + n);
		}
		free(str);
		str = get_next_line(fd);
	}
	close (fd);
	if (str)
		free(str);
	return (ft);
}

int	dol_count(char *str, int i)
{
	int	n;

	n = 0;
	while (str && str[i] && str[i] != 36)
	{
		i++;
		n++;
	}
	return (n + 1);
}

char	*dollar(t_ms *ms, char *str, int i, int n)
{
	char	*ptr;
	char	*ft;
	char	*ft2;

	ft = NULL;
	ft2 = NULL;
	while (str && str[i])
	{
		if (str && str[i] == '$')
		{
			ptr = dol2(NULL, str, i, n);
			while (ptr[n])
				n++;
			ft = dollar2(ms, ptr, n + 1, NULL);
			if (ft2)
				ft = ft_strjoin(ft2, ft);
			if (ms->dol != 0)
				ft2 = ft;
			free(ptr);
		}
		i++;
	}
	return (ft);
}

char	*dol_check(t_ms *ms, char *ptr)
{
	int		i;
	char	*ft;

	i = -1;
	ft = NULL;
	ms->dol = 0;
	while (ptr[++i])
	{
		if (ptr[i] == '$')
			ms->dol++;
	}
	if (ms->dol > 0)
		ft = dollar(ms, ptr, 0, 0);
	return (ft);
}