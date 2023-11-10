/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:59:02 by rugrigor          #+#    #+#             */
/*   Updated: 2023/11/10 19:40:22 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	if (sig == SIGINT && (g_glob == 0 || g_glob == SIGINT))
	{
		g_glob = SIGINT;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
