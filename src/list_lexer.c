/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 19:10:19 by hrahovha          #+#    #+#             */
/*   Updated: 2023/08/16 07:01:44 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	new1(t_lcmd *new)
{
	new->prev = NULL;
	new->next = NULL;
	new->lpp = NULL;
	new->lb = NULL;
	new->tree = NULL;
}

void	infos3(t_lcmd *new, char **info)
{
	if (info[0])
			new->file = info[0];
	else
		new->file = NULL;
	new->f_id = info[1];
	new->cmd = NULL;
	new->flag = NULL;
	new->word = NULL;
}

t_lexer	*lstnew(void)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->id = NULL;
	new->kw = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_lexer	*lstlast(t_lexer *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	lstadd_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*k;

	k = *lst;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	k = lstlast(*lst);
	k->next = new;
	new->prev = k;
}
