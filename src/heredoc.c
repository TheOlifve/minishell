/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:32:34 by hrahovha          #+#    #+#             */
/*   Updated: 2023/11/23 15:31:12 by hrahovha         ###   ########.fr       */
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

int	heredoc(char *str, int file, char *tmp)
{
	g_glob = 5;
	file = open("src/heredoc", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (file < 0)
		return (0);
	while (1)
	{
		sig3();
		tmp = readline("heredoc> ");
		if (g_glob == 7)
			return (270);
		if (!tmp)
			break ;
		if (ft_strcmp2(str, tmp) == -10)
			break ;
		free(tmp);
		tmp = ft_strjoin(tmp, "\n");
		ft_putstr_fd(tmp, file);
		free(tmp);
	}
	g_glob = 0;
	free(tmp);
	close(file);
	return (0);
}

int	open_files_help(t_ms *ms, char **file, int fd)
{
	fd = open(*file, O_RDWR);
	if (fd < 0)
		return (err(NULL, *file, ms, 1));
	return (fd);
}

int	open_files(t_ms *ms, char **file, int fd)
{
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
		else if (ft_strncmp(*file, "<<", 2) == 0 && *file != NULL)
		{
			*file += 2;
			fd = open("src/heredoc", O_RDWR);
		}
		else if (ft_strncmp(*file, "<", 1) == 0 && *file != NULL)
		{
			*file += 1;
			fd = open_files_help(ms, file, fd);
		}
		file++;
	}
	return (fd);
}
