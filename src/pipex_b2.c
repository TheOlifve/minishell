/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_b2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:21:29 by rugrigor          #+#    #+#             */
/*   Updated: 2023/11/21 15:51:16 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	std_dup(t_ms *ms, char **file)
{
	int		fd;
	char	*in_file;
	char	*out_file;

	fd = 0;
	in_file = in_find(file);
	out_file = out_find(file);
	if (in_file != NULL)
	{
		fd = open_files(ms, ft_split(in_file, ' '), -1);
		if (fd < 0)
			return (1);
		my_dup2(fd, 1, ms);
	}
	if (out_file != NULL)
		fd = my_dup2(0, open_files(ms, ft_split(out_file, ' '), -1), ms);
	return (fd);
}

int	child_dup(t_ms	*ms, t_pipex *pipex, char **cmd, int fd)
{
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
		if (fd < 0)
			return (1);
		if (pipex->index == pipex->cmd_cnt - 1)
			my_dup2(fd, 1, ms);
		else
			my_dup2(fd, pipex->fd[pipex->index][1], ms);
	}
	if (out_file != NULL)
		out_dup(ms, pipex, out_file);
	return (0);
}
