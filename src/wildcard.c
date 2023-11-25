/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 13:05:20 by hrahovha          #+#    #+#             */
/*   Updated: 2023/11/21 16:47:55 by rugrigor         ###   ########.fr       */
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
			ms->wd_tmp = ft_strdup(tmp);
		}
		else
			tmp = ft_strdup("");
		free(tmp);
		i++;
	}
}

char	**get_files(void)
{
	char			*tmp;
	char			*tmp2;
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
	return (ft_split(tmp2, ' '));
}

int	wildcard(t_ms *ms, char *str)
{
	char	**file;

	file = get_files();
	if (file == NULL)
		return (1);
	from_file(ms, str, file);
	if (ft_strcmp(ms->wd_tmp, "\0") == 0)
	{
		printf("minishell: no matches found: %s\n", str);
		return (1);
	}
	return (0);
}
