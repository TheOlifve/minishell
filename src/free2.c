/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 23:48:25 by rugrigor          #+#    #+#             */
/*   Updated: 2023/12/18 13:26:31 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	err2(t_ms *ms, int type)
{
	if (type == 4)
	{
		printf("minishell cd: error retrieving current directory: getcwd: ");
		printf("cannot access parent directories: No such file or directory\n");
		ms->err = 1;
		ms->exit_num = 0;
	}
	else if (type == 5)
	{
		printf("minishell cd: OLDPWD not set\n");
		ms->err = 1;
		ms->exit_num = 1;
	}
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
	else if (type == 4 || type == 5)
		err2(ms, type);
	return (1);
}

int	pars_err(char *error, t_ms *ms)
{
	printf("minishell: pars error near `%s'\n", error);
	ms->p_err = 1;
	ms->exit_num = 1;
	return (2);
}
