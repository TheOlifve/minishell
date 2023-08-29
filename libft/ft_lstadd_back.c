/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 21:52:26 by rugrigor          #+#    #+#             */
/*   Updated: 2023/01/30 19:18:42 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tsl;

	tsl = *lst;
	if (!tsl)
	{
		*lst = new;
		return ;
	}
	tsl = ft_lstlast(tsl);
	tsl -> next = new;
}
