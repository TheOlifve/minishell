/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 12:11:50 by rugrigor          #+#    #+#             */
/*   Updated: 2023/09/22 15:27:11 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// char	**ft_masjoin(char **tmp, char *str)
// {
// 	int		i;
// 	char	**mas;

// 	i = 0;
// 	if (!str)
// 		return (tmp);
// 	while (tmp && tmp[i])
// 		i++;
// 	mas = malloc(sizeof(char *) * (i + 2));
// 	i = 0;
// 	while (tmp && tmp[i])
// 	{
// 		// printf("int i - %d\n",i);
// 		mas[i] = ft_strdup(tmp[i]);
// 		i++;
// 	}
// 	mas[i] = ft_strdup(str);
// 	mas[i + 1] = NULL;
// 	return (mas);
// }

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

void	goto_start(t_ms *ms)
{
	while (ms->tree[ms->ord]->prev)
	{
		if(ms->tree[ms->ord]->prev)
			ms->tree[ms->ord] = ms->tree[ms->ord]->prev;
	}
}