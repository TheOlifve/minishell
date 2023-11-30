/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:27:39 by rugrigor          #+#    #+#             */
/*   Updated: 2023/11/30 14:00:36 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	my_dup2(int read, int write1, t_ms *ms)
{
	if (ms->prior > 0 && ms->prior < 5)
	{
		if (dup2(read, 0) < 0)
			return (my_write("minishell: Bad file descriptor\n", 1));
		if (ms->bonus2 > 0)
		{
			if (dup2(ms->bonus2, 1) < 0)
				return (my_write("minishell: Bad file descriptor\n", 1));
		}
		else if (dup2(ms->bonus, 1) < 0)
			return (my_write("minishell: Bad file descriptor\n", 1));
	}
	else
	{
		if (dup2(read, 0) < 0)
			return (my_write("minishell: Bad file descriptor\n", 1));
		if (dup2(write1, 1) < 0)
			return (my_write("minishell: Bad file descriptor\n", 1));
	}
	return (0);
}

void	bonus_dup2(t_ms *ms, int n)
{
	char	*tmp;
	int		fd;

	if (ms->bonus2 > 0)
		my_dup2(ms->bonus, ms->bonus2, ms);
	else if (ms->c2 > 0)
		my_dup2(ms->bonus, ms->c2, ms);
	else if (ms->bonus2 == 0)
		my_exit(ms->bonus, 0, ms);
	if (!ms->tree[n]->_pipe)
	{
		fd = open("bonus_help", O_RDONLY);
		tmp = get_next_line(fd);
		while(tmp)
		{
			printf("%s", tmp);
			free(tmp);
			tmp = get_next_line(fd);
		}
		close(fd);
		unlink("bonus_help");
	}
}

void	bonus_dup(t_ms *ms, int pid)
{
	int		ptr[1];
	int		n;
	
	n = ms->ord;
	if (ms->pipe_cmd == 1)
		n -= 1;
	if (ms->c1 == 1)
		ms->bonus2 = 0;
	if (ms->prior == 4 && ms->c1 == 1)
	{
		ms->prior = 5;
		pid = fork();
		if (pid == 0)
		{
			bonus_dup2(ms, n);
			exit (0);
		}
		while (wait(ptr) != -1)
			;
		ms->exit_num = ptr[0];
		if (ptr[0] > 0)
		ft_search(ms);
	}
}

int	child_dup(t_ms	*ms, t_pipex *pipex, char **cmd, int fd)
{
	char	*in_file;
	char	*out_file;
	char	**file;

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
		file = ft_split(in_file, ' ');
		fd = open_files(ms, file, -1);
		if (fd < 0)
			return (1);
		if (pipex->index == pipex->cmd_cnt - 1)
			my_dup2(fd, 1, ms);
		else
			my_dup2(fd, pipex->fd[pipex->index][1], ms);
		doublefree(file);
	}
	if (out_file != NULL)
		out_dup(ms, pipex, out_file);
	return (0);
}