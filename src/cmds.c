/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 20:28:07 by rugrigor          #+#    #+#             */
/*   Updated: 2023/08/29 13:19:58 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	echo(t_ms *ms, int i, int flag)
{
	if (ms->lcmd[i]->flag && ft_strncmp(ms->lcmd[i]->flag, "-n", 2) == 0)
		flag = 1;
	ms->lcmd[i] = ms->lcmd[i]->next;
	while (ms->lcmd[i])
	{
		if (ms->lcmd[i]->word)
		{
			printf("%s", ms->lcmd[i]->word);
			if (ms->lcmd[i]->next)
				printf(" ");
		}
		ms->lcmd[i] = ms->lcmd[i]->next;
	}
	if (flag == 0)
		printf("\n");
	return (0);
}

char	*cd2(char *ptr, char *buff, int i)
{
	char	*vp;

	while (ptr[++i])
	{
		if (ptr[i] == 32 && ptr[i + 1] == '\0')
			ptr[i] = '/';
	}
	vp = ft_strjoin(buff, (ft_strjoin("/", ptr)));
	return (vp);
}

int	cd(t_ms *ms, int i, int j)
{
	char	*vp;
	char	buff[256];
	char	*home;
	char	*ptr;

	while (ms->envp[++j])
		if (ft_strncmp(ms->envp[j], "HOME=", 5) == 0)
			home = ms->envp[j] + 5;
	if (!ms->lcmd[i]->next)
	{
		chdir(home);
		return (0);
	}
	ptr = ft_strdup(ms->lcmd[i]->next->file);
	if (ptr == NULL)
		ptr = ft_strdup(ms->lcmd[i]->next->word);
	if (getcwd(buff, 256) == NULL)
		return (perr("cd", ms));
	vp = cd2(ptr, buff, -1);
	free(ptr);
	if (chdir(vp) != 0)
		return (perr("cd", ms));
	return (pwd(ms, 0));
}

int	pwd(t_ms *ms, int mod)
{
	int		i;
	char	buff[256];
	char	*oldpwd;

	i = -1;
	if (getcwd(buff, 254) == NULL)
		return (1);
	oldpwd = NULL;
	while (ms->envp[++i])
	{
		if (ft_strncmp(ms->envp[i], "PWD=", 4) == 0)
		{
			oldpwd = ft_strdup(ms->envp[i]);
			ms->envp[i] = ft_strjoin("PWD=", buff);
			break;
		}
	}
	if (mod == 1)
		printf("%s\n", buff);
	else
		ms->envp[i + 1] = ft_strjoin("OLD",oldpwd);
	if (oldpwd)
		free(oldpwd);
	return (0);
}

int	env(t_ms *ms)
{
	int	i;

	i = -1;
	if (ft_strcmp(ms->args, "env") == 0)
	{
		while (ms->envp[++i])
			printf("%s\n", ms->envp[i]);
	}
	return (0);
}
