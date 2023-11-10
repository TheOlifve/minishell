/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:32:34 by hrahovha          #+#    #+#             */
/*   Updated: 2023/11/10 20:43:22 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_handler(int sig)
{
	// if (sig == SIGQUIT)
	// 	signal(SIGQUIT, SIG_IGN);
	// printf("gg %d", sig);
	if (sig == SIGINT)
	{
		rl_catch_signals = 0;
		(void) sig;
		// printf("\n");
		rl_replace_line("", 0);
		// rl_on_new_line();
		// rl_redisplay();
		g_glob = 2;
		rl_done = 1;
	}
}
// int	handler(void)
// {
// 	return (0);
// }

// int	sig3(void)
// {
// 	// struct sigaction	sa;
// 	// printf("aaa");
	
// 	sa.sa_handler = sig_handler;
// 	// if (g_glob == SIGINT)
// 	// {
// 	// 	g_glob = 5;
// 	// 	return (1);
// 	// }
// 	// sigemptyset(&sa.sa_mask);
// 	// sa.sa_flags = SA_RESTART;
// 	// sigaction(SIGQUIT, &sa, NULL);
// 	sigaction(SIGINT, &sa, NULL);
// 	// signal(SIGINT, SIG_IGN);
// 	// rl_event_hook = &handler;
// 	return (0);
// }

int	heredoc(char *str)
{
	struct sigaction	sa;
	int					file;
	char				*tmp;

	file = open("src/heredoc", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (file < 0)
		return (1);
	g_glob = 5;
	rl_catch_signals = 0;
	while (1)
	{
		write(1, "heredoc> ", 9);
		// sig3();
		sa.sa_handler = sig_handler;
		sigaction(SIGINT, &sa, NULL);
		// signal(SIGINT, SIG_IGN);
		rl_catch_signals = 0;
		tmp = get_next_line(0);
		// signal(SIGINT, SIG_IGN);
		rl_catch_signals = 0;
		if (g_glob == 2)
		{
			signal(SIGINT, SIG_IGN);
			printf("\n");
			unlink("src/heredoc");
			break ;
		}
		if (!tmp)
		{
			printf("\n");
			break ;
		}
		if (ft_strcmp2(str, tmp) == -10)
			break ;
		write(file, tmp, ft_strlen(tmp));
		free(tmp);
	}
	g_glob = 0;
	close(file);
	free(tmp);
	return (file);
}

int	open_files(char **file, int fd)
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
				return (err(NULL, *file, NULL, 1));
		}
		file++;
	}
	return (fd);
}
