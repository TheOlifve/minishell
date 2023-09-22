/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:00:36 by rugrigor          #+#    #+#             */
/*   Updated: 2023/09/08 02:07:41 by rugrigor         ###   ########.fr       */
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
	ms->save_stdout = dup(1);
	ms->f = 0;
	ms->c1 = 0;
	ms->c2 = 0;
	ms->ord = 0;
	ms->bool_word = 0;
	ms->dol2 = 0;
	ms->pos = 0;
	ms->cmd = 0;
	ms->pp = -1;
	ms->bb = 0;
	ms->error = 0;
	ms->index = -1;
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
			ft_free2(m_s);
		}
}

void	ft_shlvl(char **envp, t_ms *ms, int i, int n)
{
	int		j;
	char	**env;
	
	while (envp[++i])
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
		{
			envp[i] += 6;
			j = ft_atoi(envp[i]);
			j += 1;
			envp[i] = ft_strjoin("SHLVL=", ft_itoa(j));
			break;
		}
	i = 0;
	while (envp[i])
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "OLDPWD=", 7) == 0)
			i++;
		env[n++] = envp[i];
	}
	env[n] = NULL;
	ms->envp = env;
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
		system ("leaks minishell");
		exit (0);
	}
	(void) argv;
	ft_shlvl(envp, &m_s, -1, 0);
	m_s.exit_num = 0;
	while (1)
		loop(&m_s, &lexer);
}
