/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:12:25 by rugrigor          #+#    #+#             */
/*   Updated: 2023/09/07 16:41:54 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_cmd(char *path, char *cmd)
{
	int	i;
	int	j;

	if (path == NULL)
		return (0);
	i = ft_strlen(path) - 1;
	j = ft_strlen(cmd) - 1;
	if (i < j)
		return (0);
	while (j >= 0 && i >= 0)
	{
		if (path && cmd && path[i] != cmd[j])
			return (0);
		j--;
		i--;
	}
	return (1);
}

void	ft_dup2(int read, int write, t_ms *ms)
{
	if (dup2(read, 0) < 0)
		perr("Error", ms);
	if (dup2(write, 1) < 0)
		perr("Error", ms);
}

int	help_helper(char *join, char *ptr, char *lex, t_ms *ms)
{
	free(join);
	ms->ptr = ptr;
	if (ft_strncmp(lex, "./", 2) == 0)
		ms->ptr = lex;
	return (1);
}

char	*check_ft(t_ms *ms, char *ft, int i)
{
	char	*ft2;
	
	while (ft && ft[i++])
		if (ft[i] == '=')
		{
			ft2 = ft_strdup(ft + i + 1);
			ft = ft_strdup(ft2);
			free(ft2);
		}
	i = 0;
	if (ft[i] == 39 || ft[i] == 34)
	{	
		ft2 = ft_strdup(ft);
		while (ft2[i])
		{
			if (ft2[i] == 39 || ft2[i] == 34)
				ft2[i] = 32;
			i++;
		}
		ft = ft_strtrim(ft2, " ");
	}
	if (ms->ft2)
		ft = ft_strjoin(ft, ms->ft2);
	return (ft);
}
