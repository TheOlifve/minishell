/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_bb.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:11:33 by rugrigor          #+#    #+#             */
/*   Updated: 2023/11/11 00:31:02 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_search(t_ms *ms)
{
	ms->err = 1;
	while (ms && ms->index >= 0 && ms->tree[ms->index])
	{
		while (ms && ms->tree[ms->index] && ms->tree[ms->index]->prev)
			ms->tree[ms->index] = ms->tree[ms->index]->prev;
		if (ms->tree[ms->index]->_and)
		{	
			ms->bb = 8;
			break ;
		}
		ms->index++;
	}
}

void	child_help(t_pipex *pipex, t_ms *ms, char **cmd_args, int j)
{
	if (j == 1)
	{
		pipe_close(pipex);
		exit_mode(1, ms);
	}
	else if (j == 2)
	{
		pipe_close(pipex);
		execve(cmd_args[0], cmd_args, ms->envp);
		if (pipex->index == 0)
			dup2(0, STDOUT);
		printf("minishell: %s: command not found\n", cmd_args[0]);
		exit_mode(7, ms);
	}
}

int	eng(t_ms *ms)
{
	int	n;

	n = ms->ord;
	ms->index = ms->ord;
	while (ms && ms->tree[n])
	{
		if (ms->tree[n]->_or)
			return (n);
		n++;
	}
	return (-1);
}
