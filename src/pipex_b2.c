/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_b2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:21:29 by rugrigor          #+#    #+#             */
/*   Updated: 2023/11/15 20:49:08 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_cmd(t_ms *ms, char	**cmd)
{
	int		pid;
	int		ptr[1];

	pid = fork();
	if (pid == 0)
	{
		execve (cmd[0], cmd, ms->envp);
		printf("minishell: %s: command not found\n", cmd[0]);
		exit_mode(7, ms);
	}
	while (wait(ptr) != -1)
		;
	cat_exit(ms, cmd[0]);
	if (ptr[0] > 0)
	{
		ft_search(ms);
		return (1);
	}
	return (0);
}

char	*out_find(char **cmd)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	tmp = NULL;
	while (cmd && cmd[i])
	{
		if (cmd[i][0] == '>')
		{
			if (tmp == NULL)
				tmp = ft_strdup("");
			tmp2 = ft_join(tmp, cmd[i], 1);
			free(tmp);
			tmp = ft_strdup(tmp2);
			free(tmp2);
		}
		i++;
	}
	return (tmp);
}

char	*in_find(char **cmd)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	tmp = NULL;
	while (cmd && cmd[i])
	{
		if (cmd[i][0] == '<')
		{
			if (tmp == NULL)
				tmp = ft_strdup("");
			tmp2 = ft_join(tmp, cmd[i], 1);
			free(tmp);
			tmp = ft_strdup(tmp2);
			free(tmp2);
		}
		i++;
	}
	return (tmp);
}

void	out_dup(t_ms *ms, t_pipex *pipex, char *out_file)
{
	int	fd;

	fd = open_files(ms, ft_split(out_file, ' '), -1);
	if (pipex->index == 0)
		my_dup2(0, fd, ms);
	else
		my_dup2(pipex->fd[pipex->index - 1][0], fd, ms);
}

void	child_dup(t_ms	*ms, t_pipex *pipex, char **cmd)
{
	int		fd;
	char	*in_file;
	char	*out_file;

	in_file = in_find(cmd);
	out_file = out_find(cmd);
	if (pipex->index == 0 && in_file == NULL)
		my_dup2(0, pipex->fd[pipex->index][1], ms);
	else if (pipex->index == pipex->cmd_cnt - 1 && in_file == NULL)
		my_dup2(pipex->fd[pipex->index - 1][0], 1, ms);
	else if (in_file == NULL)
		my_dup2(pipex->fd[pipex->index - 1][0],
			pipex->fd[pipex->index][1], ms);
	if (in_file != NULL)
	{
		fd = open_files(ms, ft_split(in_file, ' '), -1);
		if (pipex->index == pipex->cmd_cnt - 1)
			my_dup2(fd, 1, ms);
		else
			my_dup2(fd, pipex->fd[pipex->index][1], ms);
	}
	if (out_file != NULL)
		out_dup(ms, pipex, out_file);
}
