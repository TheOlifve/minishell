/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:59:02 by rugrigor          #+#    #+#             */
/*   Updated: 2023/11/30 14:04:10 by rugrigor         ###   ########.fr       */
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
		rl_replace_line("", 0);
		rl_done = 1;
	}
}

void	main_sig(t_ms *ms)
{
	ms->bb = 0;
	ms->c1 = 0;
	ms->c2 = 0;
	ms->ord = 0;
	rl_catch_signals = 0;
	ms->sa.sa_handler = sig2;
	sigemptyset(&ms->sa.sa_mask);
	ms->sa.sa_flags = SA_RESTART;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	sigaction(SIGINT, &ms->sa, NULL);
	rl_event_hook = &handler2;
}
