/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:04:20 by hrahovha          #+#    #+#             */
/*   Updated: 2023/10/19 15:34:59 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_find_p(t_ms *ms, char **cmd)
{
	if (get_cmd(cmd[0], "export") == 1)
		return (ft_export(ms, cmd, 1));
	else if (get_cmd(cmd[0], "unset") == 1)
		return (ft_unset(ms, cmd, 1));
	else if (get_cmd(cmd[0], "echo") == 1)
		return (echo(ms, 0));
	else if (get_cmd(cmd[0], "cd") == 1)
		return (cd(ms, -1));
	else if (get_cmd(cmd[0], "pwd") == 1)
		return (pwd(ms, 1));
	else if (get_cmd(cmd[0], "env") == 1)
		return (env(ms));
	else if (get_cmd(cmd[0], "exit") == 1)
		exit_mode(0, ms);
	return (2);
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
	if (ptr[0] > 0)
	{
		ms->err = 1;
		return (1);
	}
	ms->exit_num = 0;
	return (0);
}

char	*redir_find(char **argv)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	tmp = NULL;
	while(argv && argv[i])
	{
		// dprintf(2,"argv - %s\n", argv[i]);
		if (argv[i][0] == '<' || argv[i][0] == '>')
		{
			if (tmp == NULL)
				tmp = ft_strdup("");
			tmp2 = ft_join(tmp, argv[i], 1);
			free(tmp);
			tmp = ft_strdup(tmp2);
			free(tmp2);
		}
		i++;
	}
	return (tmp);
}

int	exec_with_redir_pipe2(t_ms *ms, char **cmd, int pid)
{
	int	i;
	int	fd;
	int	ptr[1];

	fd = open("src/tmp", O_RDWR | O_TRUNC | O_CREAT, 0644);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd, 1);
		i = cmd_find(ms, cmd);
		if (i == 0)
			exit(0);
		else if (i == 1)
		{
			printf("minishell: error\n");
			exit(1);
		}
		execve (cmd[0], cmd, ms->envp);
		dup2(1, STDOUT);
		printf("minishell: %s: command not found\n", cmd[0]);
		exit_mode(7, ms);
	}
	while (wait(ptr) != -1)
		;
	return (ptr[0]);
}

char	**redir_cut(char **cmd)
{
	int		i;
	char	*tmp;
	char	*tmp1;
	char	**tmp3;

	i = 0;
	tmp1 = ft_strdup("");
	while (cmd[i])
	{
		if (cmd[i][0] == '<' || cmd[i][0] == '>')
			break;
		tmp = ft_join(tmp1, cmd[i], 1);
		free(tmp1);
		tmp1 = ft_strdup(tmp);
		free(tmp);
		i++;
	}
	tmp3 = ft_split(tmp1, ' ');
	return (tmp3);
}

int	exec_with_redir_pipe(t_ms *ms, char **cmd, char *file)
{
	int		pid;
	int		ptr;
	char	**tmp;
	
	(void)cmd;
	if (cmd[0][0] == '<' || cmd[0][0] == '>')
	{
		open_files(ft_split(file, ' '));
		return (0);
	}
	pid = 0;
	tmp = redir_cut(cmd);
	ptr = exec_with_redir_pipe2(ms, tmp, pid);
	open_files(ft_split(file, ' '));
	if (ptr > 0)
	{
		unlink("src/tmp");
		return (1);
	}
	redir(read_file(), ft_split(file, ' '));
	unlink("src/tmp");
	return (0);
}

int	child(t_ms *ms, t_pipex *pipex, char **argv)
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
		{
			perr("Error", ms);
			exit_mode(7, ms);
		}
		if (redir_find(cmd_args) != NULL)
			j = exec_with_redir_pipe(ms, cmd_args, redir_find(cmd_args));
		else
			j = cmd_find_p(ms, cmd_args);
		child_help(pipex, ms, cmd_args, j);
		exit_mode(1, ms);
	}
	return (0);
}

int	pipex(t_ms *ms, char **argv, int num)
{
	t_pipex	pipex;
	int		ptr[1];

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
		child(ms, &pipex, argv);
		pipex.cmd_crnt++;
		pipex.index += 1;
	}
	pipe_close(&pipex);
	while (wait(ptr) != -1)
		;
	if (ptr[0] > 0)
	{
		ms->err = 1;
		return (1);
	}
	return (0);
}
