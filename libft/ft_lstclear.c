/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:50:56 by rugrigor          #+#    #+#             */
/*   Updated: 2023/01/31 15:30:27 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*s;

	if (!*lst || !del)
		return ;
	while (*lst)
	{
		s = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = s;
	}
}
