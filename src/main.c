/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:00:36 by rugrigor          #+#    #+#             */
/*   Updated: 2023/08/29 19:52:08 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	main_sig(void)
{
	struct sigaction sa;

	sa.sa_handler = sig2;
	if (sigaction(SIGINT, &sa, NULL) < 0
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR
		|| signal(SIGTSTP, SIG_IGN) == SIG_ERR)
		perror("minishell_ERROR");
}

void	main2(t_ms *ms, int	i)
{
	main_sig();
	while (ms->envp[++i])
		if (ft_strncmp(ms->envp[i], "PATH=", 5) == 0)
			ms->path = ms->envp[i] + 5;
	ms->i = 0;
	ms->f = 0;
	ms->c1 = 0;
	ms->c2 = 0;
	ms->pos = 0;
	ms->cmd = 0;
	ms->pp = 0;
	ms->bb = 0;
	ms->index = 0;
	ms->args_old = NULL;
	ms->args_old = readline("minishell% ");
	ctrld(ms->args_old, ms);
	if (ms->args_old)
		add_history (ms->args_old);
	ms->num = ft_strlen(ms->args_old);
}

void	loop(t_ms *m_s, t_lexer *lexer)
{
		rl_catch_signals = 0;
		main2(m_s, -1);
		if (simbol(m_s, -1) != 0)
		{
			free(m_s->args_old);
			free(m_s->args);
			perror("minishell_ERROR");
		}
		else
		{
			tokenizer(m_s, &lexer);
			free(m_s->args_old);
		}
}

int	main(int argc, char **argv, char **envp)
{
	t_ms	m_s;
	t_lexer	lexer;

	// navak1();
	// navak2();
	if (argc > 1)
	{
		perror("minishell_ERROR");
		exit (0);
	}
	(void) argv;
	while (1)
	{
		m_s.envp = envp;
		loop(&m_s, &lexer);
	}
	unlink ("cache");
}
