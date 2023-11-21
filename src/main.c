/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:00:36 by rugrigor          #+#    #+#             */
/*   Updated: 2023/11/21 16:58:20 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	main2(t_ms *ms, int i)
{
	main_sig(ms);
	while (ms->envp[++i])
		if (ft_strncmp(ms->envp[i], "PATH=", 5) == 0)
			ms->path = ms->envp[i] + 5;
	ms->prior = 0;
	ms->p_err = 0;
	ms->index = -1;
	ms->bb = 0;
	ms->exit = 0;
	ms->c1 = 0;
	ms->c2 = 0;
	ms->ord = 0;
	ms->bool_word = 0;
	ms->dol2 = 0;
	ms->err = 0;
	ms->args_old = NULL;
	ms->args_old = readline("minishell% ");
	ctrld(ms->args_old, ms);
	if (ms->args_old)
		add_history (ms->args_old);
	if (g_glob == SIGINT)
		ms->exit_num = 1;
	ms->num = ft_strlen(ms->args_old);
}

int	loop(t_ms *m_s, t_lexer *lexer)
{
	m_s->_stdin_backup_ = dup(0);
	m_s->_stdout_backup_ = dup(1);
	g_glob = 0;
	main2(m_s, -1);
	if (ft_strcmp(m_s->args_old, "\0") == 0)
		return (0);
	if (simbol(m_s, -1) != 0)
	{
		free(m_s->args_old);
		m_s->exit_num = 1;
		pars_err("quote", m_s);
	}
	else
	{
		m_s->args = m_s->args_old;
		tokenizer(m_s, &lexer, -1, -1);
		free(m_s->args_old);
		ft_free2(m_s);
	}
	return (0);
}

void	ft_shlvl2(char **envp, t_ms *ms, int i, int n)
{
	char	**env;

	env = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "OLDPWD=", 7) == 0)
			i++;
		env[n++] = (envp[i]);
	}
	env[n] = NULL;
	ms->envp = env;
}

void	ft_shlvl(char **envp, t_ms *ms, int i, int n)
{
	int	tmp;
	int	j;

	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
		{
			envp[i] += 6;
			j = ft_atoi(envp[i]);
			free(envp[i]);
			j += 1;
			tmp = ft_itoa(j);
			envp[i] = ft_strjoin("SHLVL=", tmp);
			break ;
		}
	}
	i = 0;
	while (envp[i])
		i++;
	ft_shlvl2(envp, ms, i, n);
	free(tmp);
}

int	main(int argc, char **argv, char **envp)
{
	t_ms	m_s;
	t_lexer	lexer;

	if (argc > 1)
	{
		perror("minishell_ERROR");
		exit (1);
	}
	(void) argv;
	ft_shlvl(envp, &m_s, -1, 0);
	system("leaks minishell");
	m_s.exit_num = 0;
	while (1)
		loop(&m_s, &lexer);
}
