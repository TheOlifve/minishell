/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:04:20 by hrahovha          #+#    #+#             */
/*   Updated: 2023/12/20 17:13:22 by rugrigor         ###   ########.fr       */
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
		tmp1 = ft_strdup(tmp);
		free(tmp);
		i++;
	}
	tmp3 = ft_split(tmp1, ' ');
	free(tmp1);
	doublefree(cmd);
	return (tmp3);
}

int	heredoc_find(t_ms *ms, char **cmd_args)
{
	while (*cmd_args)
	{
		if (ft_strncmp(*cmd_args, "<<", 2) == 0 && *cmd_args != NULL)
		{
			*cmd_args += 2;
			if (ft_strcmp(*cmd_args, "\0") == 0)
			{
				*cmd_args -= 2;
				return (err(NULL, NULL, ms, 3));
			}
			g_glob = 5;
			if (heredoc(*cmd_args, 0, NULL, NULL) == 270)
			{
				g_glob = 0;
				*cmd_args -= 2;
				return (270);
			}
			else
				*cmd_args -= 2;
			g_glob = 0;
		}
		cmd_args++;
	}
	return (0);
}

int	child(t_ms *ms, t_pipex *pipex, char *argv, char **cmd_args)
{
	cmd_args = ft_split(argv, ' ');
	if (!cmd_args)
		exit_mode(3, ms);
	if (heredoc_find(ms, cmd_args) == 270)
		return (child_doc(cmd_args));
	if (check_built(cmd_args[0]))
	{
		cmd_args = ex_1(cmd_args, -1, -1);
		return (child_builtin(ms, pipex, cmd_args));
	}
	pipex->pid = fork();
	if (pipex->pid == -1)
		return (my_write2(ms, cmd_args));
	if (pipex->pid == 0)
	{
		if (cmd_args[0][0] == '<' || cmd_args[0][0] == '>')
			my_exit(open_files(ms, cmd_args, -1), 1, ms);
		my_exit(child_dup(ms, pipex, cmd_args, 0), 1, ms);
		child_help2(ms, pipex, argv);
	}
	else if (pipex->pid == 0)
		exit (0);
	cat_exit(ms, cmd_args[0]);
	doublefree(cmd_args);
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
		child(ms, &pipex, argv[pipex.cmd_crnt], NULL);
		pipex.cmd_crnt++;
		ms->ord += 1;
		pipex.index += 1;
	}
	pipe_close(&pipex);
	ms->pipe_cmd = 1;
	while (wait(ptr) != -1)
		;
	ms->exit_num = ptr[0] / 256;
	if (ptr[0] > 0)
		ft_search(ms);
}
