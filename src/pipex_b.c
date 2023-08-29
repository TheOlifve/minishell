/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:04:20 by hrahovha          #+#    #+#             */
/*   Updated: 2023/08/29 19:50:12 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_find_p(t_ms *ms, char **cmd, int i)
{
	if (get_cmd(cmd[0], "export") == 1)
		return (ft_export(ms, cmd[1]));
	else if (get_cmd(cmd[0], "unset") == 1)
		return (ft_unset(ms, cmd[1]));
	else if (get_cmd(cmd[0], "echo") == 1)
		return (echo(ms, i, 0));
	else if (get_cmd(cmd[0], "cd") == 1)
		return (cd(ms, i, -1));
	else if (get_cmd(cmd[0], "pwd") == 1)
		return (pwd(ms, 1));
	else if (get_cmd(cmd[0], "env") == 1)
		return (env(ms));
	else if (get_cmd(cmd[0], "exit") == 1)
		exit_mode(0, ms);
	return (2);
}

void	ft_dup2(int read, int write, t_ms *ms)
{
	if (dup2(read, 0) < 0)
		perr("Error", ms);
	if (dup2(write, 1) < 0)
		perr("Error", ms);
}

void	pipe_open(t_pipex *pipex, t_ms *ms)
{
	int	i;

	i = -1;
	pipex->fd = malloc(pipex->pipes_cnt * sizeof(int *));
	if (!pipex->fd)
		perr("Error", ms);
	while (++i < pipex->pipes_cnt)
	{
		pipex->fd[i] = malloc(sizeof(int) * 2);
		if (!pipex->fd[i])
			perr("Error", ms);
	}
	i = -1;
	while (++i < pipex->pipes_cnt)
		pipe(pipex->fd[i]);
}

void	child(t_ms *ms, t_pipex *pipex, char **argv, int i)
{
	int		j;
	char	**cmd_args;

	pipex->pid = fork();
	if (pipex->pid == 0)
	{
		if (pipex->index == 0)
			dup2(pipex->fd[0][1], STDOUT);
		else if (pipex->index == pipex->cmd_cnt - 1)
			dup2(pipex->fd[pipex->index - 1][0], STDIN);
		else
			ft_dup2(pipex->fd[pipex->index - 1][0], pipex->fd[pipex->index][1], ms);
		cmd_args = ft_split(argv[pipex->cmd_crnt], ' ');
		if (!cmd_args)
			perr("Error", ms);
		j = cmd_find_p(ms, cmd_args, i);
		if (j == 1)
		{
			pipe_close(pipex);
			exit_mode (2, ms);
		}
		else if (j == 2)
		{
			pipe_close(pipex);
			execve(cmd_args[0], cmd_args, ms->envp1);
			if (pipex->index == 0)
				dup2(0, STDOUT);
			printf("minishell: %s: command not found\n", cmd_args[0]);
			exit_mode (7, ms);
		}
		exit_mode(7, ms);
	}
}

int	pipex(t_ms *ms, int i, char **argv)
{
	t_pipex	pipex;
	int		num;
	int		ptr[1];

	num = -1;
	pipex.cmd_cnt = 0;
	pipex.cmd_crnt = 0;
	pipex.index = 0;
	while (argv[++num])
		pipex.cmd_cnt++;
	num = -1;
	pipex.pipes_cnt = pipex.cmd_cnt - 1;
	pipe_open(&pipex, ms);
	while (++num <= pipex.pipes_cnt)
	{	
		child(ms, &pipex, argv, i);
		pipex.cmd_crnt++;
		pipex.index += 1;
	}
	pipe_close(&pipex);
	while (wait(ptr) != -1)
		;
	ms->bb = ptr[0];
	return (0);
}
