/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:59:02 by rugrigor          #+#    #+#             */
/*   Updated: 2023/11/11 10:50:16 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handler(void)
{
	return (0);
}

int	handler2(void)
{
	return (0);
}

void	ctrld(char *line, t_ms *ms)
{
	if (!line)
	{
		printf("exit\n");
		exit_mode (4, ms);
	}
}

void	sig2(int sig)
{
	if (sig == SIGQUIT)
		g_glob = SIGQUIT;
	if (sig == SIGINT && (g_glob == 0 || g_glob == SIGINT))
	{
		g_glob = SIGINT;
		// printf("\n");
		rl_replace_line("", 0);
		// rl_on_new_line();
		// rl_redisplay();
		rl_done = 1;
	}
}
