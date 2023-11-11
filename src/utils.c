/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:12:25 by rugrigor          #+#    #+#             */
/*   Updated: 2023/11/11 17:38:29 by hrahovha         ###   ########.fr       */
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

int	ft_last(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while(str[i])
	{
		if (ft_strncmp(str[i], ">>", 2) == 0 || ft_strncmp(str[i], ">", 1) == 0)
			j = i;
		else if (ft_strncmp(str[i], "<<", 2) == 0)
			j = -3;
		else if (ft_strncmp(str[i], "<", 1) == 0)
			j = -2;
		i++;
	}
	return (j);
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
