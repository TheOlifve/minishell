/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 12:11:50 by rugrigor          #+#    #+#             */
/*   Updated: 2023/11/09 18:45:12 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_concat(char *cmd, char *opt)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	**option;

	i = 0;
	if (!cmd)
		cmd = ft_strdup("");
	tmp2 = ft_strdup(cmd);
	free(cmd);
	option = ft_split(opt, ' ');
	while (option && option[i])
	{
		tmp = ft_strdup(tmp2);
		free(tmp2);
		tmp2 = ft_strjoin(tmp, option[i]);
		free(tmp);
		i++;
	}
	cmd = ft_strjoin(tmp2, " ");
	free(tmp2);
	free(option);
	return (cmd);
}

// void	hard_bon_help(t_ms *m, char *ptr, int n, int i)
// {
// 	char	*str;
// 	char	*str2;

// 	str = ft_substr(ptr, 0, i - 1);
// 	str2 = ft_substr(ptr, i - 1, ft_strlen(ptr) - i + 2);
// 	free(ptr);
// 	if (n == 1)
// 		ptr = ft_strjoin(str, m->scope);
// 	else
// 		ptr = ft_strjoin(str, m->scope2);
// 	free(str);
// 	str = ft_strjoin(ptr, str2);
// 	free(ptr);
// 	ptr = ft_strdup(str);
// 	free(str);
// 	free(str2);
// 	i = i + 2 + ft_strlen(m->scope);
// 	if (n != 1)
// 		i = i + 2 + ft_strlen(m->scope2);
// }

int	space_help(t_ms *ms, int x, int n)
{
	char	*str1;
	char	*str2;
	int		i;

	i = x;
	while (ms->args_old && ms->args_old[--x] == 32)
			n++;
	str1 = ft_substr(ms->args_old, 0, i - n);
	str2 = ft_substr(ms->args_old, i, ft_strlen(ms->args_old) - (i - n - 1));
	free(ms->args_old);
	ms->args_old = ft_strjoin(str1, str2);
	ms->num = ms->num - n;
	return (-n - 1);
}

void	goto_start(t_ms *ms)
{
	while (ms->tree[ms->ord])
	{
		if (ms->tree[ms->ord]->prev)
			ms->tree[ms->ord] = ms->tree[ms->ord]->prev;
		else
			break ;
	}
}

int	ft_export_env(t_ms *ms, char **str, int i)
{
	ms->envp = malloc(sizeof(char *) * 2);
	ms->envp[0] = ft_strdup(str[i]);
	ms->envp[1] = NULL;
	return (0);
}

char	*ft_join(char *str, char *str2, int i)
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	if (i == 0)
		return (ft_strjoin(str, str2));
	else if (i == 2)
	{
		if (!str)
			str = ft_strdup("");
		tmp = ft_strjoin(str, str2);
		tmp2 = ft_strjoin(tmp, "|");
		free(tmp);
		return (tmp2);
	}
	else
	{
		if (!str)
			str = ft_strdup("");
		tmp = ft_strjoin(str, str2);
		tmp2 = ft_strjoin(tmp, " ");
		free(tmp);
		return (tmp2);
	}
}
