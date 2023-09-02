/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_bb.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:11:33 by rugrigor          #+#    #+#             */
/*   Updated: 2023/09/02 09:51:16 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_search(t_ms *ms)
{
	int n;
	
	ms->error = 1;
	n = ms->index;
	while (ms && ms->index >= 0 && ms->lcmd[ms->index])
	{
		while (ms && ms->lcmd[ms->index] && ms->lcmd[ms->index]->prev)
			ms->lcmd[ms->index] = ms->lcmd[ms->index]->prev;
		if (ms->lcmd[ms->index]->lb)
		{	
			ms->bb = 8;
			break ;
		}
		ms->index++;
	}
	while (ms && n >= 0 && ms->lcmd[n])
	{
		while (ms && ms->lcmd[n] && ms->lcmd[n]->prev)
			ms->lcmd[n] = ms->lcmd[n]->prev;
		if (ms->lcmd[n]->tree)
		{
			ms->pp = n;
			break ;
		}
		n++;
	}
}

void	child_help(t_pipex *pipex, t_ms *ms, char **cmd_args, int j)
{
	if (j == 1)
	{
		pipe_close(pipex);
		exit(0);
	}
	else if (j == 2)
	{
		pipe_close(pipex);
		if (ms->error == 1)
			exit (127);
		execve(cmd_args[0], cmd_args, ms->envp1);
		if (pipex->index == 0)
			dup2(0, STDOUT);
		printf("minishell: %s: command not found\n", cmd_args[0]);
		exit_mode(7, ms);
	}
}

void	prior(t_lexer *lex)
{
	char	*ptr;
	int		i;

	i = 0;
	while (lex && lex->kw && lex->kw[i])
	{
		if (lex->kw[i] == '(')
		{
			ptr = ft_strdup(lex->kw);
			free(lex->kw);
			lex->kw = ft_strtrim(ptr, "(");
			free(ptr);
		}
		else if (lex->kw[i] == ')')
		{
			ptr = ft_strdup(lex->kw);
			//free(lex->kw);
			lex->kw = ft_strtrim(ptr, ")");
			free(ptr);
		}
		i++;
	}
}

void	new7(t_ms *ms)
{
	ms->error = 0;
	ms->bb = 0;
	ms->pp = -1;
}

int	eng(t_ms *ms, int i)
{
	ms->index = i;
	ms->builtins = 0;
	while (ms && ms->lcmd[i])
	{
		if (ms->lcmd[i]->tree)
			return (i);
		i++;
	}
	return (-1);
}