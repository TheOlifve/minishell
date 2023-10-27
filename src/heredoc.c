/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:32:34 by hrahovha          #+#    #+#             */
/*   Updated: 2023/10/24 20:38:54 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	heredoc(char *str)
{
	int		file;
	char	*tmp;

	file = open("src/heredoc", O_WRONLY | O_TRUNC | O_CREAT, 0644);
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
	return (file);
}

int	redir_input(char **file)
{
	int	fd;
	while (*file)
	{
		if (ft_strncmp(*file, "<<", 2) == 0 && *file != NULL)
		{
			*file += 2;
			fd = heredoc(*file);
		}
		else if (ft_strncmp(*file, "<", 1) == 0 && *file != NULL)
		{
			*file += 1;
			fd = open(*file, O_RDONLY);
			if (fd == -1)
				return (1);
		}
		file++;
	}
	return (fd);
}

int	open_files(char **file)
{
	int	fd;

	fd = -1;
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
		else if (ft_strncmp(*file, "<<", 2) == 0 && *file != NULL)
		{
			*file += 2;
			fd = heredoc(*file);
		}
		else if (ft_strncmp(*file, "<", 1) == 0 && *file != NULL)
		{
			*file += 1;
			fd = open(*file, O_RDONLY);
			if (fd < 0)
				return (ERR2(*file));
		}
		file++;
	}
	return (fd);
}
