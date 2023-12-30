/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 13:05:20 by hrahovha          #+#    #+#             */
/*   Updated: 2023/12/30 21:50:58 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	from_file(t_ms *ms, char *str, char **file)
{
	int		i;
	char	*tmp;

	i = 0;
	ms->wd_tmp = ft_strdup("");
	while (file[i])
	{
		if (ft_strrcmp(file[i], str) == 0)
		{
			tmp = ft_strjoin(ms->wd_tmp, file[i]);
			if (ms->wd_tmp)
				free(ms->wd_tmp);
			ms->wd_tmp = ft_strjoin(tmp, " ");
		}
		else
			tmp = ft_strdup("");
		free(tmp);
		i++;
	}
}

char	*get_files(char *tmp, char *tmp2)
{
	DIR				*dir;
	struct dirent	*dent;

	dir = opendir(".");
	if (dir == NULL)
		return (NULL);
	dent = readdir(dir);
	while (dent != NULL)
	{
		if (ft_strncmp(dent->d_name, ".", 1) != 0)
		{
			tmp = ft_strjoin2(tmp2, dent->d_name);
			if (tmp2)
				free (tmp2);
			tmp2 = ft_strjoin2(tmp, " ");
			if (tmp)
				free (tmp);
		}
		dent = readdir(dir);
	}
	closedir(dir);
	return (tmp2);
}

int	wildcard3(char *str, char *tmp, char *tmp2)
{
	free(str);
	free(tmp);
	free(tmp2);
	printf("minishell: no matches found: %s\n", str);
	return (1);
}

int	wildcard2(char **file, t_ms *ms, int x, int i)
{
	char	*str;
	char	*tmp;
	char	*tmp2;

	i = x;
	while (ms->args[++x])
		if (ms->args[x] == 32)
			break ;
	tmp = ft_substr(ms->args, 0, i);
	tmp2 = ft_substr(ms->args, x, (ft_strlen(ms->args) - x));
	str = ft_substr(ms->args, i, x - i);
	from_file(ms, str, file);
	if (ft_strcmp(ms->wd_tmp, "\0") == 0)
		return (wildcard3(str, tmp, tmp2));
	free(str);
	str = ft_strjoin(tmp, ms->wd_tmp);
	free(tmp);
	free(ms->args);
	ms->args = ft_strjoin(str, tmp2);
	free(str);
	free(tmp2);
	return (0);
}

int	wildcard(t_ms *ms, int i, int x)
{
	char	*tmp;
	char	**file;

	tmp = get_files(NULL, NULL);
	file = ft_split(tmp, ' ');
	free(tmp);
	if (file == NULL)
		return (1);
	while (ms->args[++i])
	{
		if (ms->args[i] == 32)
			x = i;
		if (ms->args[i] == '*')
		{
			if (wildcard2(file, ms, x + 1, 0) == 1)
			{
				doublefree(file);
				return (1);
			}
		}
	}
	doublefree(file);
	return (0);
}
