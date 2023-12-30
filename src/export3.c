/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:32:34 by hrahovha          #+#    #+#             */
/*   Updated: 2023/12/20 15:33:39 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_for_eq(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	ft_export3(t_ms *ms, int i, int j)
{
	while (ms->envp && ms->envp[i])
	{
		j = 0;
		printf("declare -x ");
		while (ms->envp[i][j] && ms->envp[i][j] != '=')
		{
			printf("%c", ms->envp[i][j]);
			j++;
		}
		while (ms->envp[i][j] && (ms->envp[i][j + 1] != '\0'
			|| ms->envp[i][j + 1] != '\n'))
		{
			printf("%c", ms->envp[i][j]);
			if (ms->envp[i][j] == '=')
				printf("%c", 34);
			j++;
		}
		if (check_for_eq(ms->envp[i]) == 1)
			printf("%c", 34);
		printf("\n");
		i++;
	}
	return (0);
}

char	*str_replace2(t_ms *ms, char *str, char **tmp, int i)
{
	char	*tmp1;
	char	*str1;

	tmp1 = NULL;
	if (ms->export_plus == 0)
		return (str);
	while (tmp && tmp[++i])
	{
		while (tmp[i][ms->j_rep] && tmp[i][ms->j_rep] != '=')
			ms->j_rep++;
		if (tmp1 != NULL)
			free(tmp1);
		if (ft_strncmp(tmp[i], str, ms->j_rep + 1) == 0)
		{
			str1 = ft_substr(str, ms->j_rep + 1, ft_strlen(str) - ms->j_rep);
			tmp1 = ft_strjoin(tmp[i], str1);
			free(str1);
			break ;
		}
		else
			tmp1 = ft_strdup(str);
		ms->j_rep = 0;
	}
	free(str);
	return (tmp1);
}

char	*str_replace(t_ms *ms, char *str, char *str1, char *str2)
{
	int		i;
	char	*str3;

	i = -1;
	ms->export_plus = 0;
	while (str && str[++i])
	{
		if (str[i] == '+' || str[i] == '=')
			break ;
	}
	if (str[i] == '+' && str[i + 1] == '=')
	{
		str1 = ft_substr(str, 0, i);
		str2 = ft_substr(str, i + 1, ft_strlen(str) - i);
		ms->export_plus = 1;
	}
	else if (str[i] == '+' && str[i + 1] != '=')
		return (NULL);
	if (str[i - 1] == '=' || str1 == NULL || str2 == NULL)
		str3 = ft_strdup(str);
	else
		str3 = ft_strjoin(str1, str2);
	free(str2);
	free(str1);
	return (str3);
}

void	append2(t_ms *ms, int i, char **tmp, char *tmp_s)
{
	doublefree(ms->envp);
	ms->envp = malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (tmp && tmp[++i])
		ms->envp[i] = ft_strdup(tmp[i]);
	ms->envp[i] = ft_strdup(tmp_s);
	free(tmp_s);
	ms->envp[i + 1] = NULL;
}
