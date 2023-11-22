/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:32:34 by hrahovha          #+#    #+#             */
/*   Updated: 2023/11/22 18:45:10 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_find(t_ms *ms, char **cmd)
{
	if (ft_strcmp(cmd[0], "export") == 0 && cmd[1] == NULL)
		return (ft_export3(ms, 0, 0));
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (ft_export(ms, cmd, 1, 0));
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (ft_unset(ms, cmd, 1));
	else if (ft_strcmp(cmd[0], "echo") == 0)
		return (echo(ms, 0));
	else if (ft_strcmp(cmd[0], "cd") == 0)
		return (cd(ms, -1));
	else if (ft_strcmp(cmd[0], "exit") == 0 && ms->prior > 0)
		return (0);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (exit_mode(0, ms));
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (pwd(ms, 1));
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (env(ms));
	return (2);
}

// char	*cmd_builder2(t_ms *ms, char *cmd)
// {
// 	char	*tmp;
	
// 	if (ms->tree[ms->ord]->_cmd != NULL)
// 		cmd = ft_strjoin(ms->tree[ms->ord]->_cmd, " ");
// 	if (ms->tree[ms->ord]->_option != NULL)
// 		cmd = ft_concat(tmp, ms->tree[ms->ord]->_option);
// 	if (ms->tree[ms->ord]->_file != NULL)
// 		cmd = ft_concat(tmp, ms->tree[ms->ord]->_file);
// 	if (ms->tree[ms->ord]->_word != NULL)
// 		cmd = ft_concat(tmp, ms->tree[ms->ord]->_word);
// 	return (tmp);
// }

char	*cmd_builder(t_ms *ms)
{
	goto_start(ms);
	while (ms->tree[ms->ord])
	{
		if (ms->tree[ms->ord]->_cmd != NULL)
			ft_concat(ms, ms->tree[ms->ord]->_cmd);
		if (ms->tree[ms->ord]->_option != NULL)
			ft_concat(ms, ms->tree[ms->ord]->_option);;
		if (ms->tree[ms->ord]->_file != NULL)
			ft_concat(ms, ms->tree[ms->ord]->_file);;
		if (ms->tree[ms->ord]->_word != NULL)
			ft_concat(ms, ms->tree[ms->ord]->_word);;
		if (ms->tree[ms->ord]->next)
			ms->tree[ms->ord] = ms->tree[ms->ord]->next;
		else
			break ;
	}
	goto_start(ms);
	return (ms->my_cmd);
}

int	exec_builtin(t_ms *ms, char **cmd)
{
	int		i;
	char	**tmp;

	i = 0;
	if (ms->tree[ms->ord]->_redir != NULL)
	{
		tmp = ft_split(ms->tree[ms->ord]->_redir, ' ');
		i = my_exit(std_dup(ms, tmp), 2);
		doublefree(tmp);
	}
	if (i == 1)
	{
		ms->exit_num = 1;
		return (1);
	}
	i = cmd_find(ms, cmd);
	if (i == 0)
	{
		dup2(ms->_stdin_backup_, 0);
		dup2(ms->_stdout_backup_, 1);
	}
	else if (i == 1)
		ms->exit_num = 1;
	cat_exit(ms, cmd[0]);
	doublefree(cmd);
	return (0);
}

int	exec_one_cmd(t_ms *ms)
{
	char	**cmd;
	char	*tmp;
	int		pid;
	int		ptr[1];

	if (ms->tree[ms->ord]->_redir != NULL)
	{
		cmd = ft_split(ms->tree[ms->ord]->_redir, ' ');
		heredoc_find(ms, cmd);
		doublefree(cmd);
	}
	tmp = cmd_builder(ms);
	cmd = ft_split(tmp, ' ');
	if (check_built(cmd[0]))
		return (exec_builtin(ms, cmd));
	pid = fork();
	if (pid == 0)
	{
		if (ms->tree[ms->ord]->_redir != NULL || ms->prior > 0)
			my_exit(std_dup(ms, ft_split(ms->tree[ms->ord]->_redir, ' ')), 1);
		if (cmd[0] == NULL)
			exit (0);
		execve (cmd[0], cmd, ms->envp);
		my_write(cmd[0]);
		doublefree(cmd);
		exit_mode(7, ms);
	}
	while (wait(ptr) != -1)
		;
	cat_exit(ms, cmd[0]);
	if (ptr[0] > 0)
		ft_search(ms);
	doublefree(cmd);
	return (0);
}

void	exec_pipe_cmd(t_ms *ms, char *str, char *tmp, char *tmp2)
{
	char	*tmp3;
	char	**argv;

	while (ms->tree[ms->ord])
	{
		tmp = cmd_builder(ms);
		if (ms->tree[ms->ord]->_redir != NULL)
		{
			tmp3 = ft_strdup(tmp);
			free(tmp);
			tmp = ft_strjoin(tmp3, ms->tree[ms->ord]->_redir);
		}
		tmp2 = ft_join(str, tmp, 2);
		if (str)
			free(str);
		str = ft_strdup(tmp2);
		free(tmp);
		free(tmp2);
		if (ms->tree[ms->ord]->_pipe == NULL)
			break ;
		ms->ord += 1;
	}
	ms->ord = 0;
	argv = ft_split(str, '|');
	free(str);
	pipex(ms, argv, -1);
}

int	engine(t_ms *ms, int n)
{
	while (ms->tree[ms->ord])
	{
		if (!ms->tree[ms->ord])
			break ;
		if (ms->tree[ms->ord])
			goto_start(ms);
		n = eng(ms);
		if (ms->prior == 7)
			return (0);
		if (ms->tree[ms->ord]->_pipe != NULL)
			exec_pipe_cmd(ms, NULL, NULL, NULL);
		else if (ms->tree[ms->ord]->_pipe == NULL)
			exec_one_cmd(ms);
		if ((ms->bb == 8 && n == -1)
			|| (ms->ord == n && ms->err == 0))
			break ;
		else if (ms->err == 1 && n >= 0)
		{
			ms->ord = n + 1;
			engine(ms, 0);
			break ;
		}
		ms->ord += 1;
	}
	return (0);
}
