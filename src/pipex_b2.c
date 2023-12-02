/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_b2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:21:29 by rugrigor          #+#    #+#             */
/*   Updated: 2023/12/01 19:51:01 by hrahovha         ###   ########.fr       */
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

void	out_dup(t_ms *ms, t_pipex *pipex, char *out_file)
{
	int		fd;
	char	**file;

	file = ft_split(out_file, ' ');
	fd = open_files(ms, ft_split(out_file, ' '), -1);
	doublefree(file);
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
	char	**tmp;
	char	**tmp2;

	fd = 0;
	in_file = in_find(file);
	out_file = out_find(file);
	if (in_file != NULL)
	{
		tmp = ft_split(in_file, ' ');
		free(in_file);
		fd = open_files(ms, tmp, -1);
		if (fd < 0)
			return (1);
		my_dup2(fd, 1, ms);
		doublefree(tmp);
	}
	if (out_file != NULL)
	{
		tmp2 = ft_split(out_file, ' ');
		free(out_file);
		fd = my_dup2(0, open_files(ms, tmp2, -1), ms);
		doublefree(tmp2);
	}
	doublefree(file);
	// exit(0);
	return (fd);
}
