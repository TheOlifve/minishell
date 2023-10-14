/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <hrahovha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:32:34 by hrahovha          #+#    #+#             */
/*   Updated: 2023/09/07 22:30:43 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_export2(t_ms *ms, char **str, int i)
{
	int	j;
	if (!str[i])
		return (0);
	j = check_var(str[i]);
	if (j == 0)
	{
		i++;
		ft_export(ms, str, i);
	}
	else if (j == 2 || j == 3)
		return (2);
	else
		return (1);
	(void)ms;
	return (0);
}
