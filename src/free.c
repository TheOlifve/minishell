/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:04:20 by hrahovha          #+#    #+#             */
/*   Updated: 2023/09/22 18:14:27 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pars_err(char *error)
{
	printf("minishell: pars error near `%s'\n", error);
	return (2);
}

int	ERR(char *error, char *str)
{
	printf("minishell: %s: '%s': not a valid identifier\n", error, str);
	return (1);
}

int	perr(char *str, t_ms *ms)
{
	perror(str);
	ft_search(ms);
	return (1);
}

int	exit_mode(int n, t_ms *ms)
{
	if (n == 0)
	{
		ft_free2(ms);
		printf("exit\n");
		exit (0);
	}
	else if (n == 1)
		exit (0);
	else if (n == 2)
	{
		perror("minishell_ERROR");
		exit(0);
	}
	else if (n == 4)
	{
		// ft_free2(ms);
		exit (0);
	}
	else if (n == 7)
	{
		ft_search(ms);
		exit(127);
	}
	return (0);
}

void	ft_free2(t_ms *ms)
{
	ms->ord = 0;
	while (ms->tree[ms->ord])
	{
		free(ms->tree[ms->ord]);
		ms->ord += 1;
	}
	ms->ord = 0;
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
