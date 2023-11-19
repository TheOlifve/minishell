/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 20:02:08 by hrahovha          #+#    #+#             */
/*   Updated: 2023/11/17 21:00:52 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pipe_num(char *str)
{
	int	i;
	int	tmp;

	i = -1;
	tmp = 0;
	while (str && str[++i])
		;
	i--;
	while (i >= 0)
	{
		if (str[i] == '|')
			break ;
		if (str[i] != ' ')
			tmp = 1;
		i--;
	}
	return (tmp);
}

void	pipe_check(t_ms *ms)
{
	char	*tmp;
	while (pipe_num(ms->args) == 0)
	{
		tmp = ft_strdup(ms->args);
		if (ms->args)
			free(ms->args);
		ms->args = ft_join(tmp, readline("> "), ' ');
		free(tmp);
	}
}

int	my_exit(int n, int mod)
{
	if (mod == 0 && (n == 0 || n == 1))
		exit (n);
	else if (mod == 1 && (n == 1 || n < 0 ))
		exit (1);
	return (0);
}
