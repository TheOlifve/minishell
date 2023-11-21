/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 20:02:08 by hrahovha          #+#    #+#             */
/*   Updated: 2023/11/21 14:54:32 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pipe_num(char *str)
{
	int	i;
	int	tmp;

	i = -1;
	tmp = 0;
	while (str && str[++i])
		;
	i--;
	while (i >= 0)
	{
		if (str[i] == '|')
			break ;
		if (str[i] != ' ')
			tmp = 1;
		i--;
	}
	return (tmp);
}

int	child_builtin(t_ms *ms, t_pipex *pipex, char **cmd)
{
	int	i;

	i = my_exit(child_dup(ms, pipex, cmd, 0), 2);
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
	free(cmd);
	return (0);
}

int	check_built(char *str)
{
	if (!ft_strcmp(str, "pwd") || !ft_strcmp(str, "env")
		|| !ft_strcmp(str, "export") || !ft_strcmp(str, "unset")
		|| !ft_strcmp(str, "echo") || !ft_strcmp(str, "cd")
		||	!ft_strcmp(str, "exit"))
		return (1);
	return (0);
}

void	pipe_check(t_ms *ms)
{
	char	*tmp;
	while (pipe_num(ms->args) == 0)
	{
		tmp = ft_strdup(ms->args);
		if (ms->args)
			free(ms->args);
		ms->args = ft_join(tmp, readline("> "), ' ');
		free(tmp);
	}
}

int	my_exit(int n, int mod)
{
	if (mod == 0 && (n == 0 || n == 1))
		return (1);
	else if (mod == 1 && (n == 1 || n < 0 ))
		exit (1);
	if (mod == 2 && (n == 1 || n < 0 ))
		return (1);
	return (0);
}
