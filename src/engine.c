/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:32:34 by hrahovha          #+#    #+#             */
/*   Updated: 2023/09/08 12:58:12 by rugrigor         ###   ########.fr       */
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

char	*cmd_builder(t_ms *ms, int i, char *tmp, char *cmd)
{
	while (ms->lcmd[i])
	{
		if (ms->lcmd[i]->cmd)
			cmd = ft_join(tmp, ms->lcmd[i]->cmd, 1);
		free(tmp);
		tmp = ft_strdup(cmd);
		if (ms->lcmd[i]->flag)
			cmd = ft_join(tmp, ms->lcmd[i]->flag, 1);
		free(tmp);
		tmp = ft_strdup(cmd);
		if (ms->lcmd[i]->file)
			cmd = ft_join(tmp, ms->lcmd[i]->file, 1);
		free(tmp);
		tmp = ft_strdup(cmd);
		if (ms->lcmd[i]->word)
			cmd = ft_join(tmp, ms->lcmd[i]->word, 1);
		tmp = ft_strdup(cmd);
		if (ms->lcmd[i]->next)
			ms->lcmd[i] = ms->lcmd[i]->next;
		else
			break ;
	}
	return (cmd);
}

int	cmd_find(t_ms *ms, int i)
{
	char	*cmd;

	// while (ms->lcmd[0])
    // {
    //     printf("%s\n", ms->lcmd[0]->cmd);
    //     printf("%s\n", ms->lcmd[0]->flag);
    //     printf("%s\n", ms->lcmd[0]->file);
    //     printf("%s\n", ms->lcmd[0]->f_id);
    //     printf("%s\n", ms->lcmd[0]->word);
    //     printf("%s\n", ms->lcmd[0]->lpp);
    //     printf("%s\n", ms->lcmd[0]->lb);
    //     printf("%s\n", ms->lcmd[0]->tree);
    //     ms->lcmd[0] = ms->lcmd[0]->next;
    // }
    // while (ms->lcmd[1])
    // {
    //     printf("%s\n", ms->lcmd[1]->cmd);
    //     printf("%s\n", ms->lcmd[1]->flag);
    //     printf("%s\n", ms->lcmd[1]->file);
    //     printf("%s\n", ms->lcmd[1]->f_id);
    //     printf("%s\n", ms->lcmd[1]->word);
    //     printf("%s\n", ms->lcmd[1]->lpp);
    //     printf("%s\n", ms->lcmd[1]->lb);
    //     printf("%s\n", ms->lcmd[1]->tree);
    //     //ms->lcmd[1] = ms->lcmd[1]->next;
    // }
	if (ms->lcmd[i]->cmd == NULL)
		cmd = ft_strdup(ms->lcmd[i]->word);
	else
		cmd = ft_strdup(ms->lcmd[i]->cmd);
	if (get_cmd(cmd, "export") == 1)
		return (ft_export(ms, ms->lcmd[i]->next->word));
	else if (get_cmd(cmd, "unset") == 1)
		return (ft_unset(ms, ms->lcmd[i]->next->word));
	else if (get_cmd(cmd, "echo") == 1)
		return (echo(ms, i, 0));
	else if (get_cmd(cmd, "cd") == 1)
		return (cd(ms, i, -1));
	else if (get_cmd(cmd, "pwd") == 1)
		return (pwd(ms, 1));
	else if (get_cmd(cmd, "env") == 1)
		return (env(ms));
	else if (get_cmd(cmd, "exit") == 1)
		exit_mode(0, ms);
	return (2);
}

int	ft_pipe_cmd(t_ms *ms, int i)
{
	char	*str;
	char	*tmp;
	char	*tmp2;
	t_lcmd	*ptr;

	str = ft_strdup("");
	while (ms->lcmd[i])
	{
		ptr = ms->lcmd[i];
		tmp = cmd_builder(ms, i, ft_strdup(""), NULL);
		ms->lcmd[i] = ptr;
		tmp2 = ft_join(str, tmp, 2);
		free(str);
		str = ft_strdup(tmp2);
		free(tmp);
		free(tmp2);
		if (ms->lcmd[i]->lpp == NULL)
			break;
		i++;
	}
	ms->p_argv = ft_split(str, '|');
	ms->index = i;
	pipex(ms, i, ms->p_argv, -1);
	return (i);
}

int	engine(t_ms *ms, int i, int n)
{
	new7(ms);
	while (*ms->lcmd && ms->lcmd[i])
	{
		if (!ms->lcmd[i])
			break ;
		n = eng(ms, i);
		if (ms->lcmd[i]->lpp)
			i = ft_pipe_cmd(ms, i);
		else
		{
			if (cmd_find(ms, i) == 2)
				exec_cmd(ms, i);
		}
		if ((ms->bb == 8 && n == -1)
			|| (i == n && ms->error == 0))
			break ;
		else if (ms->error == 1 && n >= 0)
		{
			engine(ms, n + 1, 0);
			break ;
		}
		i++;
	}
	return (0);
}
