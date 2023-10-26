/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_bb.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:11:33 by rugrigor          #+#    #+#             */
/*   Updated: 2023/10/26 15:21:59 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_search(t_ms *ms)
{
	// int n;
	
	ms->err = 1;
	// n = ms->index;
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
// 	while (ms && n >= 0 && ms->tree[n])
// 	{
// 		while (ms && ms->tree[n] && ms->tree[n]->prev)
// 			ms->tree[n] = ms->tree[n]->prev;
// 		if (ms->tree[n]->tree)
// 		{
// 			ms->pp = n;
// 			break ;
// 		}
// 		n++;
// 	}
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
		// if (ms->error == 1)
		// 	exit_mode(7, ms);
		execve(cmd_args[0], cmd_args, ms->envp);
		if (pipex->index == 0)
			dup2(0, STDOUT);
		printf("minishell: %s: command not found\n", cmd_args[0]);
		exit_mode(7, ms);
	}
}

void	new7(t_ms *ms)
{
	ms->err = 0;
	ms->bb = 0;
	// ms->pp = -1;
}

int	eng(t_ms *ms)
{
	int	n;

	n = ms->ord;
	ms->index = ms->ord;
	// ms->builtins = 0;
	while (ms && ms->tree[n])
	{
		if (ms->tree[n]->_or)
			return (n);
		n++;
	}
	return (-1);
}