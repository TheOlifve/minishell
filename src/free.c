/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:04:20 by hrahovha          #+#    #+#             */
/*   Updated: 2023/08/29 13:34:31 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	perr(char *str, t_ms *ms)
{
	perror(str);
	//search(ms);
	(void)ms;
	return (1);
}

void	exit_mode(int n, t_ms *ms)
{
	ft_free2(ms);
	if (n == 0)
	{
		printf("exit\n");
		exit (0);
	}
	else if (n == 4)
		exit (0);
	else if (n == 7)
		exit(127);
}

void	ft_free2(t_ms *ms)
{
	int	i;

	i = 0;
	if (ms->lcmd[i])
	{
		while (ms->lcmd[i])
		{
			free(ms->lcmd[i]);
			i++;
		}
	}
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
	free(pipex->fd);
}
