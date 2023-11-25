/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:32:34 by hrahovha          #+#    #+#             */
/*   Updated: 2023/11/09 18:43:37 by rugrigor         ###   ########.fr       */
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

int	check_var2(char *str)
{
	int		i;
	int		len;

	i = 0;
	if ((str[i] > 64 && str[i] < 91) || (str[i] > 96 && str[i] < 123)
		|| (str[i] == '_'))
		;
	else
		return (-1);
	len = ft_strlen(str);
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=' && str[i + 1] == '\0')
		return (-3);
	if (str[i] != '=')
		return (-2);
	if (len < 3)
		return (-1);
	if (str[i] && ((str[i - 1] && str[i - 1] == 32)
			|| (str[i + 1] && str[i + 1] == 32)))
		return (-1);
	return (i);
}

int	check_var3(char *str, int i, int j, t_ms *ms)
{
	while (str && str[i] && i <= j)
	{
		if (((str[i] > 64 && str[i] < 91) || (str[i] > 96 && str[i] < 123)
				|| (str[i] > 47 && str[i] < 58)) || (str[i] == '=')
			|| (str[i] == '+' && str[i + 1] == '=' ) || str[i] == '_')
				i++;
		else
			return (err("export", str, ms, 0));
	}
	return (0);
}

int	check_var4(char **str, int i)
{
	int	j;

	j = 0;
	while (str[i] && str[i][j])
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
			err("export", str[i + 1], ms, 0);
			return (3);
		}
	}
	j = check_var(str[i], ms);
	if (j == 0)
	{
		i++;
		ft_export(ms, str, i, 0);
	}
	else if (j == 2 || j == 3)
		return (2);
	else
		return (1);
	(void)ms;
	return (0);
}
