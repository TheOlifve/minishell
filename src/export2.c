/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:32:34 by hrahovha          #+#    #+#             */
/*   Updated: 2023/10/19 15:18:44 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_export3(t_ms *ms, int i, int j)
{
	while (ms->envp && ms->envp[i])
	{
		j = 0;
		printf("declare -x ");
		while (ms->envp[i][j])
		{
			if (ms->envp[i][j] == '=')
			{
				printf("%c", ms->envp[i][j]);
				printf("%c", 34);
			}
			else if (ms->envp[i][j + 1] == '\0' || ms->envp[i][j + 1] == '\n')
			{
				printf("%c", ms->envp[i][j]);
				printf("%c", 34);
			}
			else
				printf("%c", ms->envp[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	return (0);
}

int	check_var4(char **str, int i)
{
	int	j;

	j = 0;
	while(str[i] && str[i][j])
	{
		if (str[i][j] == '=')
			return (0);
		j++;
	}
	if (str[i + 1][0] == '=')
		return (2);
	return (0);
}

int	ft_export2(t_ms *ms, char **str, int i)
{
	int	j;
	if (!str[i])
		return (0);
	if (str[i] && str[i + 1])
	{
		if (check_var4(str, i) == 2)
		{
			ERR("export", str[i + 1], ms);
			return (3);
		}
	}
	j = check_var(str[i], ms);
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
