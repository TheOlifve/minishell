/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_b2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:21:29 by rugrigor          #+#    #+#             */
/*   Updated: 2023/11/09 18:38:44 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_find_p(t_ms *ms, char **cmd)
{
	if (get_cmd(cmd[0], "export") == 1)
		return (ft_export(ms, cmd, 1, 0));
	else if (get_cmd(cmd[0], "unset") == 1 && !cmd[1])
		return (ft_export3(ms, 0, 0));
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
	else if (get_cmd(cmd[0], "exit") == 1 && ms->exit == 5)
		;
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
		ms->exit_num = ptr[0];
		ft_search(ms);
		return (1);
	}
	ms->exit_num = ptr[0];
	return (0);
}

char	*redir_find(char **argv)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	tmp = NULL;
	while (argv && argv[i])
	{
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

void	exec_with_redir_pipe3(int i)
{
	if (i == 0)
		exit(0);
	else if (i == 1)
	{
		printf("minishell: error\n");
		exit(1);
	}
}
