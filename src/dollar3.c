/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:57:45 by rugrigor          #+#    #+#             */
/*   Updated: 2023/09/08 16:00:16 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	*slash2(t_ms *ms, char *ptr, char *ft, char *ft2)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	j = 0;
	n = 0;
	while (ptr && ptr[i])
	{
		if (ptr[i] == '/' || (i > 0 && ft_isdigit(ptr[i]) == 1
			&& ft_isdigit(ptr[i - 1]) == 1) || ptr[i] == '.')
		{
			ft[j] = '\0';
			ft2[n++] = ptr[i];
		}
		else if (ft[j] != '\0')
			ft[j++] = ptr[i];
		else
			ft2[n++] = ptr[i];
		i++;
	}
	ft2[n] = '\0';
	ms->ft2 = ft2;
	return (ft);
}

char	*slash(t_ms *ms, char *ptr, int i)
{
	char	*ft;
	char	*ft2;

	ft = NULL;
    ms->dol = ms->dol - 1;
	while (ptr && ptr[i])
	{
		if (ptr[i] == '/' || (i > 0 && ft_isdigit(ptr[i]) == 1
			&& ft_isdigit(ptr[i - 1]) == 1) || ptr[i] == '.')
		{
			ft = malloc(sizeof(char) * i + 1);
			ft2 = malloc(sizeof(char) * (ft_strlen(ptr) - i + 1));
			if (!ft || !ft2)
				return (NULL);
			break ;
		}
		i++;
	}
	i = 0;
	if (ft && ft2)
		return (slash2(ms, ptr, ft, ft2));
	return (ptr);
}
