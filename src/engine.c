/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:32:34 by hrahovha          #+#    #+#             */
/*   Updated: 2023/10/25 12:47:57 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_join(char *str, char *str2, int i)
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	if (i == 0)
		return (ft_strjoin(str, str2));
	else if (i == 2)
	{
		if (!str)
			str = ft_strdup("");
		tmp = ft_strjoin(str, str2);
		tmp2 = ft_strjoin(tmp, "|");
		free(tmp);
		return (tmp2);
	}
	else
	{
		if (!str)
			str = ft_strdup("");
		tmp = ft_strjoin(str, str2);
		tmp2 = ft_strjoin(tmp, " ");
		free(tmp);
		return (tmp2);
	}
}

int	cmd_find(t_ms *ms, char **cmd)
{
	if (ft_strcmp(cmd[0], "export") == 0 && cmd[1] == NULL)
		return (ft_export3(ms, 0, 0));
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (ft_export(ms, cmd, 1));
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (ft_unset(ms, cmd, 1));
	else if (ft_strcmp(cmd[0], "echo") == 0 || ft_strcmp(cmd[0], "ECHO") == 0)
		return (echo(ms, 0));
	else if (ft_strcmp(cmd[0], "cd") == 0)
		return (cd(ms, -1));
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (exit_mode(0, ms));
	else if (ft_strcmp(cmd[0], "pwd") == 0 || ft_strcmp(cmd[0], "PWD") == 0)
		return (pwd(ms, 1));
	else if (ft_strcmp(cmd[0], "env") == 0 || ft_strcmp(cmd[0], "ENV") == 0)
		return (env(ms));
	return (2);
}

char	*cmd_builder(t_ms *ms)
{
	char	*cmd;

	cmd = ft_strdup("");
	goto_start(ms);
	while (ms->tree[ms->ord])
	{
		if (ms->tree[ms->ord]->_cmd != NULL)
			cmd = ft_strjoin(ms->tree[ms->ord]->_cmd, " ");
		if (ms->tree[ms->ord]->_option != NULL)
			cmd = ft_concat(cmd, ms->tree[ms->ord]->_option);
		if (ms->tree[ms->ord]->_file != NULL)
			cmd = ft_concat(cmd, ms->tree[ms->ord]->_file);
		if (ms->tree[ms->ord]->_word != NULL)
			cmd = ft_concat(cmd, ms->tree[ms->ord]->_word);
		if (ms->tree[ms->ord]->next)
			ms->tree[ms->ord] = ms->tree[ms->ord]->next;
		else
			break ;
	}
	goto_start(ms);
	return (cmd);
}

int	exec_one_cmd(t_ms *ms)
{
	int		i;
	char	**cmd;

	if (ms->tree[ms->ord]->_redir != NULL)
		return (exec_with_redir(ms));
	cmd = ft_split(cmd_builder(ms), ' ');
	i = cmd_find(ms, cmd);
	if (i == 2)
		i = exec_cmd(ms, cmd);
	free(cmd);
	// printf("%d\n", ms->err);
	return (i);
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
			break;
		ms->ord += 1;
	}
	argv = ft_split(str, '|');
	pipex(ms, argv, -1);
	// printf("%d\n", ms->err);
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
		(void)n;
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

// int	eufind(char *str)
// {
// 	if (ft_strcmp(str, "export") == 0 ||
// 		ft_strcmp(str, "unset") == 0)
// 			return (0);
// 	return (1);
// }

// int	cmd_find(t_ms *ms, int i)
// {
// 	char	*cmd;

// 	else if (get_cmd(cmd, "cd") == 1)
// 		return (cd(ms, i, -1));
// 	else if (get_cmd(cmd, "pwd") == 1)
// 		return (pwd(ms, 1));
// 	else if (get_cmd(cmd, "exit") == 1)
// 		exit_mode(0, ms);
// 	else if (eufind(cmd) == 0 && !ms->lcmd[i]->next)
// 		return (1);

// 	return (2);
// }