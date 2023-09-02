/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 12:11:50 by rugrigor          #+#    #+#             */
/*   Updated: 2023/09/02 02:45:40 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	*check_ft(char *ft, int n)
{
	char	*ft2;
	
	if (ft[n] == 39 || ft[n] == 34)
	{	
		ft2 = ft_strdup(ft);
		while (ft2[n])
		{
			if (ft2[n] == 39 || ft2[n] == 34)
				ft2[n] = 32;
			n++;
		}
		ft = ft_strtrim(ft2, " ");
	}
	return (ft);
}