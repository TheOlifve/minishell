/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_bb.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:11:33 by rugrigor          #+#    #+#             */
/*   Updated: 2023/11/20 00:36:06 by rugrigor         ###   ########.fr       */
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

// void	child_help(t_pipex *pipex, t_ms *ms, char **cmd_args, int check)
// {
// 	if (check == 1)
// 	{
// 		pipe_close(pipex);
// 		exit_mode(1, ms);
// 	}
// 	else if (check == 2)
// 	{
// 		pipe_close(pipex);
// 		execve(cmd_args[0], cmd_args, ms->envp);
// 		if (pipex->index == 0)
// 			dup2(0, STDOUT);
// 		printf("minishell: %s: command not found\n", cmd_args[0]);
// 		exit_mode(7, ms);
// 	}
// }
