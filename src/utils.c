/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:12:25 by rugrigor          #+#    #+#             */
/*   Updated: 2023/11/21 15:50:26 by rugrigor         ###   ########.fr       */
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

int	my_dup2(int read, int write1, t_ms *ms)
{
	if (ms->prior > 0 && ms->prior < 5)
	{
		dup2(0, 0);
		dup2(ms->bonus, 1);
		if (ms->prior == 4)
		{
			dup2(ms->bonus, 0);
			dup2(write1, 0);
		}
	}
	else
	{
		if (dup2(read, 0) < 0)
		{
			perr("Error", ms);
			return (-1);
		}
		if (dup2(write1, 1) < 0)
		{
			perr("Error", ms);
			return (-1);
		}
	}
	return (0);
}

int	help_helper(char *join, char *ptr, char *lex, t_ms *ms)
{
	free(join);
	ms->ptr = ptr;
	if (ft_strncmp(lex, "./", 2) == 0)
		ms->ptr = lex;
	return (1);
}

void	pipe_close(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->pipes_cnt)
	{
		close(pipex->fd[i][0]);
		close(pipex->fd[i][1]);
		if (pipex->fd[i])
			free(pipex->fd[i]);
		i++;
	}
	i = -1;
	free(pipex->fd);
}
