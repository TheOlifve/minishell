/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_bb.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:11:33 by rugrigor          #+#    #+#             */
/*   Updated: 2023/12/20 17:14:42 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exit4(t_ms *ms, char **cmd)
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	if (cmd[1])
	{
		tmp2 = ft_strtrim(cmd[1], ")");
		tmp = ft_strdup(tmp2);
		free(tmp2);
	}
	ms->exit_num = (unsigned char)ft_atoi(tmp);
	free(tmp);
	return (0);
}

void	child_help2(t_ms *ms, t_pipex *pipex, char *argv)
{
	char	**cmd_args;

	cmd_args = redir_cut(ft_split(argv, ' '));
	cmd_args = ex_1(cmd_args, -1, -1);
	if (cmd_args[0] == NULL)
		exit (0);
	pipe_close(pipex);
	execve(cmd_args[0], cmd_args, ms->envp);
	my_write(cmd_args[0], 0);
	exit_mode(7, ms);
}

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

void	child_help(t_pipex *pipex, t_ms *ms, char **cmd_args, int check)
{
	if (check == 1)
	{
		pipe_close(pipex);
		exit_mode(1, ms);
	}
	else if (check == 2)
	{
		pipe_close(pipex);
		execve(cmd_args[0], cmd_args, ms->envp);
		if (pipex->index == 0)
			dup2(0, STDOUT);
		printf("minishell: %s: command not found\n", cmd_args[0]);
		exit_mode(7, ms);
	}
}

char	*dollar4(t_ms *ms, char *ft2, char *ptr, int n)
{
	char	*ft;
	char	*ft3;

	ft = dollar2(ms, ptr, n + 1, NULL);
	ms->dol--;
	if (ft2)
	{
		ft3 = ft_strdup(ft);
		free(ft);
		ft = ft_strjoin(ft2, ft3);
		free(ft3);
	}
	return (ft);
}
