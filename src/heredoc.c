/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:32:34 by hrahovha          #+#    #+#             */
/*   Updated: 2023/09/22 16:01:23 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	her_print(void)
{
	int		file;
	char	*tmp;

	file = open("heredoc", O_RDONLY, 0644);
	tmp = get_next_line(file);
	while (tmp)
	{
		printf("%s", tmp);
		free(tmp);
		tmp = get_next_line(file);
	}
	close(file);
	free(tmp);
}

int	heredoc(char *str)
{
	int		file;
	char	*tmp;

	file = open("heredoc", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (file < 0)
		return (1);
	while (1)
	{
		write(1, "heredoc> ", 9);
		tmp = get_next_line(0);
		if (!tmp)
			break ;
		if (ft_strcmp(str, tmp) == -10)
			break ;
		write(file, tmp, ft_strlen(tmp));
		free(tmp);
	}
	close(file);
	free(tmp);
	her_print();
	unlink("heredoc");
	return (0);
}

int	redir(char *str, char **file)
{
	int		fd;

	fd = 0;
	while (*file)
	{
		if (ft_strncmp(*file, ">>", 2) == 0 && *file != NULL)
		{
			*file += 2;
			fd = open(*file, O_RDWR | O_APPEND | O_CREAT, 0644);
		}
		else if (ft_strncmp(*file, ">", 1) == 0 && *file != NULL)
		{
			*file += 1;
			fd = open(*file, O_RDWR | O_TRUNC | O_CREAT, 0644);
		}
		if (fd < 0)
			break ;
		write(fd, str, ft_strlen(str));
		close(fd);
		file++;
	}
	if (fd < 0)
		return (1);
	return (0);
}

void	open_files(char **file)
{
	while (*file)
	{
		if (ft_strncmp(*file, ">>", 2) == 0 && *file != NULL)
		{
			*file += 2;
			open(*file, O_RDWR | O_APPEND | O_CREAT, 0644);
		}
		else if (ft_strncmp(*file, ">", 1) == 0 && *file != NULL)
		{
			*file += 1;
			open(*file, O_RDWR | O_TRUNC | O_CREAT, 0644);
		}
		file++;
	}
}

int	redir_loop(t_ms *ms)
{
	char	*_read;
	char	*tmp;
	char	*tmp2;
	char	**file;
	
	tmp2 = ft_strdup("");
	while (1)
	{
		_read = get_next_line(0);
		if (!_read)
			break;
		tmp = ft_strjoin(tmp2, _read);
		free(tmp2);
		tmp2 = ft_strdup(tmp);
		free(tmp);
	}
	printf("%s\n",ms->tree[ms->ord]->_redir);
	file = ft_split(ms->tree[ms->ord]->_redir, ' ');
	if (redir(tmp2, file) == 1)
	{
		free(file);
		free(tmp2);
		return (1);
	}
	free(tmp2);
	return (0);
}
