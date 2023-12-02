/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:47:43 by rugrigor          #+#    #+#             */
/*   Updated: 2023/12/01 15:27:00 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*priority3(char *str, char *ptr, int i, int x)
{
	int	n;

	n = -1;
	str = (char *)malloc(sizeof(char) * (ft_strlen(ptr) - x + 4));
	i = 0;
	while (ptr && ptr[++n])
	{
		if (ptr[n] == 4)
		{
			n++;
			if (!ptr[n])
				break ;
		}
		str[i] = ptr[n];
		i++;
	}
	str[i] = '\0';
	free(ptr);
	return (str);
}

char	*priority2(t_ms *ms, char *str, char *ptr, int n)
{
	int	x;
	int	i;

	x = 0;
	i = -1;
	if (ms->tree[n] && !(ms->tree[n]->_redir))
		ms->c1 = 1;
	while (str && str[++i])
	{
		if (str[i] == '(' || str[i] == ')')
		{
			str[i] = 4;
			x++;
		}
	}
	ptr = ft_strdup(str);
	free(str);
	return (priority3(NULL, ptr, 0, x));
}

void	file_cmd3(t_ms *ms, char **file, int i)
{
	if (file && file[i] && file[i + 1])
	{
		i++;
		ms->c2 = open_files(ms, &file[i], 0);
	}
}

int	file_cmd2(char **file, int i, int j)
{
	while (file[i] && file[i][++j])
		if (file[i] && file[i][j] != ')' && file[i][j + 1] == ')')
			return (2);
	return (0);
}

void	file_cmd(t_ms *ms, int i, char *tmp)
{
	char	**file;

	file = ft_split(ms->tree[ms->ord]->_redir, ' ');
	while (ms->tree[ms->ord]->_redir && file[++i] && ms->x == 0)
	{
		ms->x = file_cmd2(&file[i], i, -1);
		if (ms->x == 2)
			tmp = ft_strtrim(ft_strdup(file[i]), ")");//leak
		else
			tmp = ft_strdup(file[i]);
		if (ft_strncmp(file[i], ">>", 2) == 0 && file[i] != NULL)
			ms->bonus2 = open(tmp + 2, O_RDWR | O_APPEND | O_CREAT, 0644);
		else if (ft_strncmp(file[i], ">", 1) == 0 && file[i] != NULL)
			ms->bonus2 = open(tmp + 1, O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (ms->x == 2 && ms->c1 == 1)
			file_cmd3(ms, &file[i], i);
		free(tmp);
	}
	doublefree(file);
}
