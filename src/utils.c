/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:12:25 by rugrigor          #+#    #+#             */
/*   Updated: 2023/11/20 12:26:19 by rugrigor         ###   ########.fr       */
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

void	my_dup2(int read, int write, t_ms *ms)
{
	if (ms->prior > 0 && ms->prior < 5)
	{
		printf("aaa\n");
		if (access("bonus_help", F_OK) != 0)
			ms->bonus = open("bonus_help", O_RDWR | O_APPEND | O_CREAT, 0644);
		dup2(read, 0);
		dup2(ms->bonus, 1);
	}
	else if (ms->prior == 5)
	{
		ms->prior = 0;
		if (dup2(ms->bonus, 0) < 0)
			perr("Error", ms);
		if (dup2(write, 1) < 0)
			perr("Error", ms);
	}
	else
	{
		if (dup2(read, 0) < 0)
			perr("Error", ms);
		if (dup2(write, 1) < 0)
			perr("Error", ms);
	}
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
