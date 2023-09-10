/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:38:53 by rugrigor          #+#    #+#             */
/*   Updated: 2023/09/08 16:02:04 by rugrigor         ###   ########.fr       */
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

void	dol_cmp(int fd, char *str)
{
	close (fd);
	if (str)
		free(str);
}

char	*dollar2(t_ms *ms, char *ptr, char *ft)
{
	char	*str2;
	char	*str;
	int		fd;

	if (!ptr)
		return (NULL);
	fd = open("cache", O_RDONLY);
	ptr = slash(ms, ptr, 0);
	if (ptr[0] == '\0')
		return (ft_strdup("$"));
	str = get_next_line(fd);
	while (str)
	{
		if (ptr != 0 && ft_strncmp(ft_strjoin(ptr, "="),
				str, ft_strlen(ptr) + 1) == 0)
		{
			str2 = ft_strtrim(str, "\n");
			ft = check_ft(ms, str2, 0);
		}
		free(str);
		str = get_next_line(fd);
	}
	dol_cmp(fd, str);
	return (ft);
}

char	*dollar(t_ms *ms, char *str, int i, int n)
{
	char	*ptr;
	char	*ft;
	char	*ft2;

	ft = NULL;
	ft2 = NULL;
	while (str && str[++i])
		if (str && str[i] == '$')
		{
			if (ms->ft2)
				ms->ft2  = NULL;
			ptr = dol2(NULL, str, i, n);
			ft = dollar2(ms, ptr, NULL);
			if (!ft && ms->ft2)
				ft = ms->ft2;
			else if (ft[0] == '$' && ms->ft2)
				ft = ft_strjoin(ft, ms->ft2);
			if (ft2)
				ft = ft_strjoin(ft2, ft);
			if (ms->dol != 0)
				ft2 = ft;
			free(ptr);
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
	ms->ft2 = NULL;
	while (ptr[++i])
	{
		
		if (ptr[i] == '$')
			ms->dol++;
	}
	if (ms->dol > 0)
		ft = dollar(ms, ptr, -1, 0);		
	return (ft);
}
