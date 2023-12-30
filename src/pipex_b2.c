/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_b2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:21:29 by rugrigor          #+#    #+#             */
/*   Updated: 2023/12/10 19:53:59 by rugrigor         ###   ########.fr       */
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
			tmp = ft_strdup(tmp2);
			free(tmp2);
		}
		i++;
	}
	return (tmp);
}

int	out_dup(t_ms *ms, t_pipex *pipex, char **cmd)
{
	int		fd;
	char	*out_file;
	char	**file;

	out_file = out_find(cmd);
	if (out_file != NULL)
	{
		file = ft_split(out_file, ' ');
		free(out_file);
		fd = open_files(ms, file, -1);
		doublefree(file);
		if (fd < 0)
			return (1);
		if (pipex->index == 0)
			my_dup2(0, fd, ms);
		else
			my_dup2(pipex->fd[pipex->index - 1][0], fd, ms);
	}
	return (0);
}

int	std_out_dup(t_ms *ms, char **file, int fd)
{
	char	*out_file;
	char	**tmp;

	out_file = out_find(file);
	if (out_file != NULL)
	{
		tmp = ft_split(out_file, ' ');
		free(out_file);
		fd = my_dup2(0, open_files(ms, tmp, -1), ms);
		if (fd < 0)
		{
			doublefree(tmp);
			doublefree(file);
			return (-1);
		}
		doublefree(tmp);
	}
	return (fd);
}

int	std_dup(t_ms *ms, char **file, int fd)
{
	char	*in_file;
	char	**tmp;

	in_file = in_find(file);
	if (in_file != NULL)
	{
		tmp = ft_split(in_file, ' ');
		free(in_file);
		fd = open_files(ms, tmp, -1);
		if (fd < 0)
		{
			doublefree(tmp);
			doublefree(file);
			return (-1);
		}
		my_dup2(fd, 1, ms);
		doublefree(tmp);
	}
	fd = std_out_dup(ms, file, fd);
	doublefree(file);
	return (fd);
}
