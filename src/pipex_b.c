/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:04:20 by hrahovha          #+#    #+#             */
/*   Updated: 2023/11/20 18:17:19 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	heredoc_find(t_ms *ms, char **cmd_args)
{
	char	*tmp_cmd;
	while (*cmd_args)
	{
		if (ft_strncmp(*cmd_args, "<<", 2) == 0 && *cmd_args != NULL)
		{
			tmp_cmd = *cmd_args;
			*cmd_args += 2;
			if (ft_strcmp(*cmd_args, "\0") == 0)
				return (err(NULL, NULL, ms, 3));
			heredoc(*cmd_args, 0, NULL);
			*cmd_args = tmp_cmd;
		}
		cmd_args++;
	}
	return (0);
}

// int	child_dup_built(t_ms *ms, t_pipex *pipex, char **cmd)
// {
// 	int		fd;
// 	char	*in_file;
// 	char	*out_file;

// 	in_file = in_find(cmd);
// 	out_file = out_find(cmd);
// 	(void)out_file;
// 	(void)fd;
// 	if (pipex->index == 0 && in_file == NULL)
// 	{
// 		dprintf(2, "!\n");
// 		my_dup2(0, pipex->fd[pipex->index][1], ms);
// 	}
// 	else if (pipex->index == pipex->cmd_cnt - 1 && in_file == NULL)
// 	{
// 		dprintf(2, "!!\n");
// 		my_dup2(pipex->fd[pipex->index - 1][0], 1, ms);
// 	}
// 	else if (in_file == NULL)
// 	{
// 		my_dup2(pipex->fd[pipex->index - 1][0],
// 			pipex->fd[pipex->index][1], ms);
// 	}
// 	return (0);
// }

int	check_built(char *str)
{
	if (!ft_strcmp(str, "pwd") || !ft_strcmp(str, "env")
		|| !ft_strcmp(str, "export") || !ft_strcmp(str, "unset")
		|| !ft_strcmp(str, "echo") || !ft_strcmp(str, "cd")
		||	!ft_strcmp(str, "exit"))
		return (1);
	return (0);
}

int	child_builtin(t_ms *ms, t_pipex *pipex, char **cmd)
{
	int	i;

	i = my_exit(child_dup(ms, pipex, cmd), 2);
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

int	child(t_ms *ms, t_pipex *pipex, char *argv)
{
	char	**cmd_args;
	
	cmd_args = ft_split(argv, ' ');
	if (!cmd_args)
		exit_mode(3, ms);
	heredoc_find(ms, cmd_args);
	if (check_built(cmd_args[0]))
		return (child_builtin(ms, pipex, cmd_args));
	pipex->pid = fork();
	if (pipex->pid == 0)
	{
		if (cmd_args[0][0] == '<' || cmd_args[0][0] == '>')
			my_exit(open_files(ms, cmd_args, -1), 1);
		my_exit(child_dup(ms, pipex, cmd_args), 1);
		cmd_args = redir_cut(ft_split(argv, ' '));
		if (cmd_args[0] == NULL)
			exit (0);
		pipe_close(pipex);
		execve(cmd_args[0], cmd_args, ms->envp);
		my_write(cmd_args[0]);
		exit_mode(7, ms);
	}
	else if (pipex->pid == 0)
		exit (0);
	cat_exit(ms, cmd_args[0]);
	free(cmd_args);
	return (0);
}


void	pipex(t_ms *ms, char **argv, int num)
{
	int		ptr[1];
	t_pipex	pipex;

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
		child(ms, &pipex, argv[pipex.cmd_crnt]);
		pipex.cmd_crnt++;
		ms->ord += 1;
		pipex.index += 1;
	}
	pipe_close(&pipex);
	while (wait(ptr) != -1)
		;
	if (ptr[0] > 0)
		ft_search(ms);
}
