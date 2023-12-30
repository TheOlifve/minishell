/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:16:23 by rugrigor          #+#    #+#             */
/*   Updated: 2023/12/19 19:57:12 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	chdir4(t_ms *ms)
{
	chdir("..");
	err(NULL, NULL, ms, 4);
}

void	heredoc2(int file, char *tmp)
{
	if (tmp)
		free(tmp);
	close(file);
}

void	goto_start2(t_ms *ms, int i)
{
	while (ms->tree[i])
	{
		if (ms->tree[i]->prev)
			ms->tree[i] = ms->tree[i]->prev;
		else
			break ;
	}
}

char	*cd2_help(char *vp, char *ptr, char *buff, char *tmp)
{
	if (buff)
	{
		tmp = ft_strjoin("/", ptr);
		vp = ft_strjoin(buff, tmp);
		free(tmp);
	}
	else
		return (ft_strdup(ptr));
	return (vp);
}

int	is_plus(t_ms *ms, int i, int plus)
{
	if (ms->export_plus == 1)
	{
		if (plus == 0)
			i += 1;
		else if (plus == 1)
			i -= 1;
	}
	return (i);
}
