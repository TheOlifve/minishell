/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:10:06 by rugrigor          #+#    #+#             */
/*   Updated: 2023/12/22 11:35:57 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_one_fork(t_ms *ms, char **cmd)
{
	int	pid;
	int	ptr[1];

	ptr[0] = 1;
	pid = fork();
	if (pid == 0)
	{
		if (ms->tree[ms->ord]->_redir != NULL || ms->prior > 0)
			my_exit(std_dup(ms,
					ft_split(ms->tree[ms->ord]->_redir, ' '), 0), 1, ms);
		if (cmd[0] == NULL)
			exit (0);
		execve (cmd[0], cmd, ms->envp);
		my_write(cmd[0], 0);
		exit_mode(7, ms);
	}
	while (wait(&ptr[0]) != -1)
		;
	ms->exit_num = ptr[0] / 256;
	cat_exit(ms, cmd[0]);
	if (ptr[0] > 0)
		ft_search(ms);
	doublefree(cmd);
}

char	**ex_1(char **cmd, int i, int j)
{
	while (cmd[++i])
	{
		j = -1;
		while (cmd[i][++j])
			if (cmd[i][j] == 6)
				cmd[i][j] = 32;
	}
	return (cmd);
}

int	exec_one_cmd(t_ms *ms)
{
	char	*tmp;
	char	**cmd;

	tmp = cmd_builder(ms);
	if (ms->tree[ms->ord]->_redir != NULL)
	{
		cmd = ft_split(ms->tree[ms->ord]->_redir, ' ');
		if (heredoc_find(ms, cmd) == 270)
		{
			doublefree(cmd);
			return (270);
		}
		if (tmp == NULL)
			open_files(ms, cmd, 0);
		doublefree(cmd);
		if (tmp == NULL)
			return (0);
	}
	cmd = ft_split(tmp, ' ');
	cmd = ex_1(cmd, -1, -1);
	free(tmp);
	if (check_built(cmd[0]))
		return (exec_builtin(ms, cmd));
	exec_one_fork(ms, cmd);
	return (0);
}

int	bonus_file(t_ms *ms)
{
	char	**file;

	if (ms->tree[ms->ord])
		goto_start(ms);
	while (ms->tree[ms->ord])
	{
		if (ms->tree[ms->ord]->_redir)
		{
			file = ft_split(ms->tree[ms->ord]->_redir, ' ');
			open_files(ms, file, 0);
			doublefree(file);
		}
		ms->ord += 1;
	}
	return (0);
}

char	*cmd_builder(t_ms *ms)
{
	char	*tmp;

	tmp = NULL;
	goto_start(ms);
	while (ms->tree[ms->ord])
	{
		if (ms->tree[ms->ord]->_cmd != NULL)
			ft_concat(ms, ms->tree[ms->ord]->_cmd, -1, NULL);
		if (ms->tree[ms->ord]->_option != NULL)
			ft_concat(ms, ms->tree[ms->ord]->_option, -1, NULL);
		if (ms->tree[ms->ord]->_file != NULL)
			ft_concat(ms, ms->tree[ms->ord]->_file, -1, NULL);
		if (ms->tree[ms->ord]->_word != NULL)
			ft_concat(ms, ms->tree[ms->ord]->_word, -1, NULL);
		if (ms->tree[ms->ord]->next)
			ms->tree[ms->ord] = ms->tree[ms->ord]->next;
		else
			break ;
	}
	goto_start(ms);
	tmp = ft_strdup(ms->my_cmd);
	free(ms->my_cmd);
	ms->my_cmd = NULL;
	return (tmp);
}
