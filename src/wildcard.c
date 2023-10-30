/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 13:05:20 by hrahovha          #+#    #+#             */
/*   Updated: 2023/08/21 12:26:07 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_ex(t_ms *ms, int file)
{
	char	*tmp[2];

	dup2(file, 1);
	tmp[0] = "ls";
	tmp[1] = NULL;
	execve ("/bin/ls", tmp, ms->envp);
}

void	from_file(t_ms *ms, char *str)
{
	char	*tmp;
	char	*tmp2;
	int		file;

	file = open("src/wild", O_RDONLY, 0644);
	ms->wd_tmp = ft_strdup("");
	tmp = get_next_line(file);
	while (tmp)
	{
		if (ft_strrcmp(tmp, str) == 0)
		{
			tmp2 = ft_strjoin(ms->wd_tmp, tmp);
			if (ms->wd_tmp)
				free(ms->wd_tmp);
			ms->wd_tmp = ft_strdup(tmp2);
		}
		else
			tmp2 = ft_strdup("");
		free(tmp2);
		free(tmp);
		tmp = get_next_line(file);
	}
	free(tmp);
}

char	*get_files(t_ms *ms, char *str)
{
	int		file;
	int		pid;

	file = open("src/wild", O_RDWR | O_TRUNC | O_CREAT, 0644);
	pid = fork();
	if (pid == 0)
		ft_ex(ms, file);
	while (wait(NULL) != -1)
		;
	from_file(ms, str);
	unlink ("src/wild");
	return (str);
}

int	wildcard(t_ms *ms, char *str)
{
	get_files(ms, str);
	return (0);
}
