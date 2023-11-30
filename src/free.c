/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:04:20 by hrahovha          #+#    #+#             */
/*   Updated: 2023/11/30 14:36:30 by rugrigor         ###   ########.fr       */
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
	else if (type == 4)
	{
		printf("minishell cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
		ms->err = 1;
		ms->exit_num = 0;
	}
	return (1);
}

void	ft_exit(t_ms *ms, int n)
{
	int		fd;
	char	*fd2;
	
	if (access("exit_file", F_OK) != 0)
		open("exit_file", O_RDWR | O_TRUNC | O_CREAT, 0644);
	ms->exit_num = ft_atoi(ms->tree[ms->ord]->next->_word);
		fd = open("exit_file", O_RDWR);
	fd2 = ft_itoa(ms->exit_num);
	write(fd, fd2, ft_strlen(fd2));
	n = ms->exit_num;
	close(fd);
	ft_free2(ms);
	exit (n);
}

int	exit_mode(int n, t_ms *ms)
{
	if (n == 0)
	{
		printf("exit\n");
		if (ms->tree[ms->ord]->next && ms->tree[ms->ord]->next->_word)
			ft_exit(ms, n);
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
