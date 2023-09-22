/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:32:34 by hrahovha          #+#    #+#             */
/*   Updated: 2023/09/02 09:25:49 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// char	*ft_join(char *str, char *str2, int i)
// {
// 	char	*tmp;
// 	char	*tmp2;

// 	tmp = NULL;
// 	tmp2 = NULL;
// 	if (i == 0)
// 		return (ft_strjoin(str, str2));
// 	else if (i == 2)
// 	{
// 		if (!str)
// 			str = ft_strdup("");
// 		tmp = ft_strjoin(str, str2);
// 		tmp2 = ft_strjoin(tmp, "|");
// 		free(tmp);
// 		return (tmp2);
// 	}
// 	else
// 	{
// 		if (!str)
// 			str = ft_strdup("");
// 		tmp = ft_strjoin(str, str2);
// 		tmp2 = ft_strjoin(tmp, " ");
// 		free(tmp);
// 		return (tmp2);
// 	}
// }


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

// 	if (ms->lcmd[i]->cmd == NULL)
// 		cmd = ft_strdup(ms->lcmd[i]->word);
// 	else
// 		cmd = ft_strdup(ms->lcmd[i]->cmd);
// 	if (get_cmd(cmd, "echo") == 1)
// 		return (echo(ms, i, 0));
// 	else if (get_cmd(cmd, "cd") == 1)
// 		return (cd(ms, i, -1));
// 	else if (get_cmd(cmd, "pwd") == 1)
// 		return (pwd(ms, 1));
// 	else if (get_cmd(cmd, "env") == 1)
// 		return (env(ms));
// 	else if (get_cmd(cmd, "exit") == 1)
// 		exit_mode(0, ms);
// 	else if (eufind(cmd) == 0 && !ms->lcmd[i]->next)
// 		return (1);
// 	else if (get_cmd(cmd, "export") == 1)
// 		return (ft_export(ms, ms->lcmd[i]->next->word));
// 	else if (get_cmd(cmd, "unset") == 1 && ms->lcmd[i]->next)
// 		return (ft_unset(ms, ms->lcmd[i]->next->word));
// 	return (2);
// }
int	cmd_find(t_ms *ms, char **cmd)
{
	if (ft_strcmp(cmd[0], "export") == 0)
		return (ft_export(ms, cmd, 1));
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (ft_unset(ms, cmd, 1));
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (env(ms));
	return (2);
}

char	**cmd_builder(t_ms *ms)
{
	char	*cmd;
	char	**r_cmd;

	cmd = ft_strdup("");
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
		ms->tree[ms->ord] = ms->tree[ms->ord]->next;
	}
	r_cmd = ft_split(cmd, ' ');
	free(cmd);
	return (r_cmd);
}

int	exec_one_cmd(t_ms *ms)
{
	int		i;
	char	**cmd;

	if (ms->tree[ms->ord]->_redir != NULL)
		return (exec_with_redir(ms));
	cmd = cmd_builder(ms);
	i = cmd_find(ms, cmd);
	if (i == 2)
		i = exec_cmd(ms, cmd);
	free(cmd);
	return (i);
}

int	exec_pipe_cmd(t_ms *ms)
{
	(void)ms;
	// char	*tmp;

	// printf("!\n");
	// while (ms->tree[ms->ord])
	// {
	// 	// tmp = cmd_builder(ms);
	// 	printf("%s\n",tmp);
	// 	// tmp2 = ft_join(str, tmp, 2);
	// 	// free(str);
	// 	// str = ft_strdup(tmp2);
	// 	// free(tmp);
	// 	// free(tmp2);
	// 	// if (ms->lcmd[i]->lpp == NULL)
	// 	// 	break;
	// 	// i++;
	// }
	// // ms->p_argv = ft_split(str, '|');
	// // ms->index = i;
	// // pipex(ms, i, ms->p_argv, -1);
	// // return (i);
	return (0);
}

int	engine(t_ms *ms)
{
	while (ms->tree[ms->ord])
	{
		goto_start(ms);
		if (ms->tree[ms->ord]->_pipe != NULL)
			exec_pipe_cmd(ms);
		else if (ms->tree[ms->ord]->_pipe == NULL)
			exec_one_cmd(ms);
		ms->ord += 1;
	}
	return (0);
}
