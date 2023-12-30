/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:04:20 by hrahovha          #+#    #+#             */
/*   Updated: 2023/12/30 22:06:25 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit2(t_ms *ms, unsigned long long num, int fd)
{
	char	*fd2;
	char	*n;

	if (ms->tree[ms->ord]->next && ms->tree[ms->ord]->next->_word)
	{
		n = "9223372036854775807\0";
		if (ft_isdigit2(ms->tree[ms->ord]->next->_word)
			&& ft_strlen(ms->tree[ms->ord]->next->_word) <= 19
			&& ft_strcmp3(ms->tree[ms->ord]->next->_word, n) <= 0)
			num = ft_atoi(ms->tree[ms->ord]->next->_word);
		else
		{
			printf("minishell: exit: %s: numeric argument required\n",
				ms->tree[ms->ord]->next->_word);
			num = 255;
		}
	}
	fd2 = ft_itoa((unsigned char)num);
	write(fd, fd2, ft_strlen(fd2));
	free(fd2);
	close(fd);
	ft_free2(ms, 0);
	exit (num);
}

void	ft_exit(t_ms *ms, unsigned long long num)
{
	int		fd;
	char	*n;

	if (access("exit_file", F_OK) != 0)
		open("exit_file", O_RDWR | O_TRUNC | O_CREAT, 0644);
	fd = open("exit_file", O_RDWR);
	if (ms->tree[ms->ord] && ms->tree[ms->ord]->_option)
	{
		n = "-9223372036854775807\0";
		if (ft_isdigit2(ms->tree[ms->ord]->_option)
			&& ft_strlen(ms->tree[ms->ord]->_option) <= 20
			&& ft_strcmp3(ms->tree[ms->ord]->_option, n) <= 0)
			num = ft_atoi(ms->tree[ms->ord]->_option);
		else
		{
			printf("minishell: exit: %s: numeric argument required\n",
				ms->tree[ms->ord]->_option);
			num = 255;
		}
	}
	ft_exit2(ms, num, fd);
}

int	exit_mode(int n, t_ms *ms)
{
	if (n == 0)
	{
		printf("exit\n");
		if (ms->tree[ms->ord] && ms->tree[ms->ord]->next
			&& ms->tree[ms->ord]->next->next
			&& (ms->tree[ms->ord]->next->next->_option
				|| ms->tree[ms->ord]->next->next->_word))
			return (exit_mode_cut(ms));
		else if ((ms->tree[ms->ord] && ms->tree[ms->ord]->_option)
			|| (ms->tree[ms->ord]->next && ms->tree[ms->ord]->next->_word))
			ft_exit(ms, 0);
		ft_free2(ms, 0);
		exit (0);
	}
	if (n == 1 || n == 4)
		exit (0);
	if (n == 3)
		perr("Error", ms);
	if (n == 7)
		ms->err = 1;
	if (n == 7 || n == 3)
		exit(127);
	return (0);
}

void	ft_free2_2(t_ms *ms, int i)
{
	while (ms->tree[i])
	{
		if (ms->tree[i]->_cmd)
			free(ms->tree[i]->_cmd);
		if (ms->tree[i]->_and)
			free(ms->tree[i]->_and);
		if (ms->tree[i]->_file)
			free(ms->tree[i]->_file);
		if (ms->tree[i]->_option)
			free(ms->tree[i]->_option);
		if (ms->tree[i]->_or)
			free(ms->tree[i]->_or);
		if (ms->tree[i]->_pipe)
			free(ms->tree[i]->_pipe);
		if (ms->tree[i]->_redir)
			free(ms->tree[i]->_redir);
		if (ms->tree[i]->_word)
			free(ms->tree[i]->_word);
		if (ms->tree[i]->next)
			ms->tree[i] = ms->tree[i]->next;
		else
			break ;
		free(ms->tree[i]->prev);
	}
	free(ms->tree[i]);
}

void	ft_free2(t_ms *ms, int i)
{
	while (ms->tree[ms->ord])
		ms->ord++;
	while (i < ms->ord)
	{
		if (ms->tree[i] != NULL)
		{
			goto_start2(ms, i);
			ft_free2_2(ms, i);
		}
		ms->tree[i] = NULL;
		i++;
	}
	free(ms->args);
	if (ms->wd_tmp != NULL)
		free(ms->wd_tmp);
	if (ms->my_cmd)
		free(ms->my_cmd);
	if (ms->path)
		free(ms->path);
	if (ms->str)
		doublefree(ms->str);
	ms->str = NULL;
	ms->ord = 0;
}
