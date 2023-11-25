/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:38:53 by rugrigor          #+#    #+#             */
/*   Updated: 2023/11/23 15:21:07 by hrahovha         ###   ########.fr       */
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
	char	*str;
	int		i;

	if (!ptr)
		return (NULL);
	if (ptr[0] == '?')
		return (exit_num(ms));
	i = -1;
	while (ms->envp[++i])
	{
		if (ptr != 0 && ft_strncmp(ft_strjoin(ptr, "="),
				ms->envp[i], ft_strlen(ptr) + 1) == 0)
		{
			str = ft_strtrim(ms->envp[i], "\n");
			ft = (str + n);
		}
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
			ft = dollar2(ms, ptr, n + 1, NULL);
			ms->dol--;
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
