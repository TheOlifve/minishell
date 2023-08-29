/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_bb.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:11:33 by rugrigor          #+#    #+#             */
/*   Updated: 2023/08/29 19:13:18 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_search(t_ms *ms)
{
	while (ms && ms->index > 0 && ms->lcmd[ms->index])
	{
		while (ms->lcmd[ms->index]->prev)
			ms->lcmd[ms->index] = ms->lcmd[ms->index]->prev;
		if (ms->lcmd[ms->index]->lb)
		{	
			ms->bb = 8;
			break ;
		}
		ms->index++;
	}
}