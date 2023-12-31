/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:12:25 by rugrigor          #+#    #+#             */
/*   Updated: 2023/12/18 13:26:13 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*exit_num(t_ms *ms)
{
	int		fd;
	char	*tmp;

	if (access("exit_file", F_OK) != 0)
		open("exit_file", O_RDWR | O_TRUNC | O_CREAT, 0644);
	fd = open("exit_file", O_RDWR);
	tmp = get_next_line(fd);
	if (tmp && ft_atoi(tmp) == 0)
		return (ft_itoa(ms->exit_num));
	else if (tmp)
	{
		close(fd);
		fd = open("exit_file", O_RDWR | O_TRUNC | O_CREAT, 0644);
		write (fd, 0, 2);
		return (tmp);
	}
	return (ft_itoa(ms->exit_num));
}

int	ft_chdir2(t_ms *ms, char *ptr, char *vp)
{
	if (ptr && ptr[0] && !(ptr[0] == '-'))
		free(vp);
	else if (ptr && ptr[0] && ptr[0] == '-')
	{
		free(ptr);
		return (err(NULL, NULL, ms, 5));
	}
	free(ptr);
	return (perr("minishell: cd", ms));
}

int	perr(char *str, t_ms *ms)
{
	perror(str);
	ms->err = 1;
	ms->exit_num = 1;
	return (1);
}

int	get_cmd(char *path, char *cmd)
{
	int	i;
	int	j;

	if (path == NULL)
		return (0);
	i = ft_strlen(path) - 1;
	j = ft_strlen(cmd) - 1;
	if (i < j)
		return (0);
	while (j >= 0 && i >= 0)
	{
		if (path && cmd && path[i] != cmd[j])
			return (0);
		j--;
		i--;
	}
	return (1);
}

void	pipe_close(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->pipes_cnt)
	{
		close(pipex->fd[i][0]);
		close(pipex->fd[i][1]);
		if (pipex->fd[i])
			free(pipex->fd[i]);
		i++;
	}
	i = -1;
	free(pipex->fd);
}
