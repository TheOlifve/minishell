/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:43:51 by rugrigor          #+#    #+#             */
/*   Updated: 2023/12/22 11:24:55 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*pwd2(t_ms *ms)
{
	int		i;
	int		j;
	char	*tmp;
	char	*tmp2;

	i = -1;
	j = -1;
	while (ms->envp[++i])
	{
		if (ft_strncmp(ms->envp[i], "PWD=", 4) == 0)
		{
			tmp = ft_strdup(ms->envp[i] + 4);
			j = -1;
			while (tmp[++j])
			{
				if (tmp[j] && tmp[j + 1] && tmp[j + 2] && tmp[j] == '/'
					&& tmp[j + 1] == '.' && tmp[j + 2] == '.')
					return (tmp);
			}
			tmp2 = ft_strjoin(tmp, "/..");
			free(tmp);
			return (tmp2);
		}
	}
	return (NULL);
}

void	dol_prep4(t_ms *ms, int i, char *ptr, char *ptr2)
{
	if (i == 1)
	{
		ptr = ft_substr(ms->args_old, 1, ft_strlen(ms->args_old));
		free(ms->args_old);
		ms->args_old = ft_strdup(ptr);
		free(ptr);
	}
	else
	{
		ptr = ft_substr(ms->args_old, 0, i - 1);
		ptr2 = ft_substr(ms->args_old, i, ft_strlen(ms->args_old) - i);
		free(ms->args_old);
		ms->args_old = ft_strjoin(ptr, ptr2);
		free(ptr);
		free(ptr2);
	}
}

int	child_doc(char **cmd_args)
{
	doublefree(cmd_args);
	return (270);
}

int	exit_mode_cut(t_ms *ms)
{
	printf("minishell: exit: too many arguments\n");
	ms->exit_num = 1;
	return (-1);
}
