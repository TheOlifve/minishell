/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:32:34 by hrahovha          #+#    #+#             */
/*   Updated: 2023/12/20 15:24:38 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_glob = 7;
		rl_replace_line("", 0);
		rl_done = 1;
	}
}

void	sig3(void)
{
	struct sigaction	sa;

	rl_catch_signals = 0;
	sa.sa_handler = sig_handler;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
	rl_event_hook = &handler;
}

int	heredoc(char *str, int file, char *tmp, char *tmp2)
{
	file = open("src/heredoc", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (file < 0)
		return (0);
	while (1)
	{
		sig3();
		tmp = readline("heredoc> ");
		if (g_glob == 7)
		{
			free(tmp);
			return (270);
		}
		if (!tmp)
			break ;
		if (ft_strcmp2(str, tmp) == -10)
			break ;
		tmp2 = ft_strdup(tmp);
		free(tmp);
		tmp = ft_strjoin(tmp2, "\n");
		free(tmp2);
		ft_putstr_fd(tmp, file);
		free(tmp);
	}
	heredoc2(file, tmp);
	return (0);
}

int	open_files_help(t_ms *ms, char **file, int fd)
{
	while (*file)
	{
		if (ft_strncmp(*file, "<<", 2) == 0 && *file != NULL)
		{
			*file += 2;
			fd = open("src/heredoc", O_RDWR);
			*file -= 2;
		}
		else if (ft_strncmp(*file, "<", 1) == 0 && *file != NULL)
		{
			*file += 1;
			fd = open(*file, O_RDWR);
			if (fd < 0)
			{
				err(NULL, *file, ms, 1);
				*file -= 1;
				return (-2);
			}
			*file -= 1;
		}
		file++;
	}
	return (fd);
}

int	open_files(t_ms *ms, char **file, int fd)
{
	char	**file2;

	file2 = file;
	while (*file)
	{
		if (ft_strncmp(*file, ">>", 2) == 0 && *file != NULL)
		{
			*file += 2;
			fd = open(*file, O_RDWR | O_APPEND | O_CREAT, 0644);
			*file -= 2;
		}
		else if (ft_strncmp(*file, ">", 1) == 0 && *file != NULL)
		{
			*file += 1;
			fd = open(*file, O_RDWR | O_TRUNC | O_CREAT, 0644);
			*file -= 1;
		}
		file++;
	}
	fd = open_files_help(ms, file2, fd);
	return (fd);
}
