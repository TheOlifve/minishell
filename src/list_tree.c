/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:01:20 by rugrigor          #+#    #+#             */
/*   Updated: 2023/10/25 13:47:36 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tree	*tree_new(void)
{
	t_tree		*new;

	new = malloc(sizeof(t_tree));
	if (new == 0)
		return (NULL);
	new->_cmd = NULL;
	new->_option = NULL;
	new->_redir = NULL;
	new->_file = NULL;
	new->_word = NULL;
	new->_pipe = NULL;
	new->_and = NULL;
	new->_or = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_tree	*tree_last(t_tree *lst)
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

void	tree_add_back(t_tree **tree, t_tree *new)
{
	t_tree	*tmp;

	tmp = *tree;
	if (!*tree)
	{
		*tree = new;
		return ;
	}
	tmp = tree_last(*tree);
	tmp->next = new;
	new->prev = tmp;
}
