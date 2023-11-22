/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:04:20 by hrahovha          #+#    #+#             */
/*   Updated: 2023/11/22 17:15:24 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pars_err(char *error, t_ms *ms)
{
	printf("minishell: pars error near `%s'\n", error);
	ms->p_err = 1;
	ms->exit_num = 1;
	return (2);
}

int	err(char *error, char *str, t_ms *ms, int type)
{
	if (type == 0)
	{
		printf("minishell: %s: `%s': not a valid identifier\n", error, str);
		ms->err = 1;
		ms->exit_num = 1;
	}
	else if (type == 1)
	{
		printf("minishell: %s: No such file or directory\n", str);
		ms->exit_num = 1;
		return (-2);
	}
	else if (type == 3)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		ms->exit_num = 258;
		return (-2);
	}
	return (1);
}

int	perr(char *str, t_ms *ms)
{
	perror(str);
	ms->err = 1;
	ms->exit_num = 1;
	return (1);
}

int	exit_mode(int n, t_ms *ms)
{
	if (n == 0)
	{
		printf("exit\n");
		if (ms->tree[ms->ord]->next && ms->tree[ms->ord]->next->_word)
		{
			ms->exit_num = ft_atoi(ms->tree[ms->ord]->next->_word);
			n = ms->exit_num;
			ft_free2(ms);
			exit (n);
		}
		ft_free2(ms);
		exit (0);
	}
	else if (n == 1)
		exit (0);
	if (n == 4)
		exit (0);
	if (n == 3)
		perr("Error", ms);
	if (n == 7)
		ms->err = 1;
	if (n == 7 || n == 3)
		exit(127);
	return (0);
}

void	ft_free2(t_ms *ms)
{
	ms->ord = 0;
	while (ms->tree[ms->ord])
	{
		if (ms->tree[ms->ord] != NULL)
			free(ms->tree[ms->ord]);
		ms->tree[ms->ord] = NULL;
		ms->ord += 1;
	}
	ms->ord = 0;
}
