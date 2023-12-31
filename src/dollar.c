/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:38:53 by rugrigor          #+#    #+#             */
/*   Updated: 2023/12/18 19:56:32 by rugrigor         ###   ########.fr       */
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
		ft = ft_strdup(str2 + n);
	else
	{
		ft2 = ft_strjoin(ft, str2 + n);
		ft = ft_strdup(ft2);
		free(ft2);
	}
	free(str2);
	return (ft);
}

char	*dollar2(t_ms *ms, char *ptr, int n, char *ft)
{
	char	*str;
	char	*str2;
	int		i;

	if (!ptr)
		return (NULL);
	if (ptr[0] == '?')
		return (exit_num(ms));
	i = -1;
	while (ms->envp[++i])
	{
		str2 = ft_strjoin(ptr, "=");
		if (ptr != 0 && ft_strncmp(str2, ms->envp[i], ft_strlen(ptr) + 1) == 0)
		{
			str = ft_strtrim(ms->envp[i], "\n");
			ft = ft_strdup(str + n);
			free(str);
		}
		free(str2);
	}
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
			if (ft)
				free(ft);
			ft = dollar4(ms, ft2, ptr, n);
			if (ms->dol != 0)
				ft2 = ft_strdup(ft);
			free(ptr);
		}
		i++;
	}
	free(ft2);
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
