/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:04:20 by hrahovha          #+#    #+#             */
/*   Updated: 2023/11/10 14:35:45 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_with_redir_pipe2(t_ms *ms, char **cmd, char *file, int fd2)
{
	int	i;
	int	pid;
	int	fd;
	int	ptr[1];

	fd = open("src/tmp", O_RDWR | O_TRUNC | O_CREAT, 0644);
	pid = fork();
	if (pid == 0)
	{
		if (fd2 >= 0)
			dup2(fd2, 0);
		if (ft_last(ft_split(file, ' ')) >= 0)
			dup2(fd, 1);
		i = cmd_find(ms, cmd);
		exec_with_redir_pipe3(i);
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
			break ;
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
	int		fd;
	int		ptr;
	char	**tmp;

	if (cmd[0][0] == '<' || cmd[0][0] == '>')
		return (open_files(ft_split(file, ' '), -1));
	tmp = redir_cut(cmd);
	fd = open_files(ft_split(file, ' '), -1);
	if (fd == -2)
		return (1);
	ptr = exec_with_redir_pipe2(ms, tmp, file, fd);
	if (ptr > 0)
	{
		unlink("src/tmp");
		return (1);
	}
	redir(read_file(1), ft_split(file, ' '));
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
			ft_dup2(pipex->fd[pipex->index - 1][0],
				pipex->fd[pipex->index][1], ms);
		cmd_args = ft_split(argv[pipex->cmd_crnt], ' ');
		if (!cmd_args)
			exit_mode(3, ms);
		if (redir_find(cmd_args) != NULL)
			j = exec_with_redir_pipe(ms, cmd_args, redir_find(cmd_args));
		else
			j = cmd_find_p(ms, cmd_args);
		child_help(pipex, ms, cmd_args, j);
		exit_mode(1, ms);
	}
	return (0);
}

void	pipex(t_ms *ms, char **argv, int num)
{
	t_pipex	pipex;
	int		ptr[1];

	pipex.cmd_cnt = 0;
	pipex.cmd_crnt = 0;
	pipex.index = 0;
	ptr[0] = 0;
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
		ft_search(ms);
	ms->exit_num = ptr[0];
}
