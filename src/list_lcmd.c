/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_lcmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:01:20 by rugrigor          #+#    #+#             */
/*   Updated: 2023/09/18 21:59:05 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	infos(char **info, t_ms *ms)
{
	if (info[1] && (info[1][0] == '<' || info[1][0] == '>'))
		return (3);
	if (ms->cmd == 0 && help(info[0], ms, -1, NULL) != 0)
	{
		ms->cmd = 1;
		return (1);
	}
	else if (access(info[0], F_OK) == 0)
		return (2);
	return (4);
}

void	infos2(t_lcmd *new, char **info, int i)
{
	if (i == 2)
	{
		new->file = info[0];
		if (info[1])
			new->f_id = info[1];
		else
			new->f_id = NULL;
		new->cmd = NULL;
		new->flag = NULL;
		new->word = NULL;
	}
	else if (i == 3)
		infos3(new, info);
	else
	{
		new->word = info[0];
		new->cmd = NULL;
		new->flag = NULL;
		new->file = NULL;
		new->f_id = NULL;
	}
}

t_lcmd	*lcmd_new(char	**info, t_ms *ms)
{
	t_lcmd		*new;
	int			i;

	new = malloc(sizeof(t_lcmd));
	if (new == 0)
		return (NULL);
	new1(new);
	i = infos(info, ms);
	if (i == 1)
	{
		new->cmd = ms->ptr;
		if (info[1])
			new->flag = info[1];
		else
			new->flag = NULL;
		new->file = NULL;
		new->f_id = NULL;
		new->word = NULL;
	}
	else
		infos2(new, info, i);
	return (new);
}

t_lcmd	*lcmd_last(t_lcmd *lst)
{
	while (lst)
	{
		if (lst->next)
			lst = lst->next;
		else
			return (lst);
	}
	return (NULL);
}

void	lcmd_add_back(t_lcmd **tree, char **info, t_ms *ms)
{
	t_lcmd	*tsl;
	t_lcmd	*new;

	tsl = *tree;
	if (!tsl)
	{
		ms->cmd = 0;
		*tree = lcmd_new(info, ms);
		ms->lcmd[ms->i] = *tree;
		ms->i++;
		return ;
	}
	else
		new = lcmd_new(info, ms);
	tsl = lcmd_last(tsl);
	tsl->next = new;
	new->prev = tsl;
}
