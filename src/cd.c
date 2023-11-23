/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:44:07 by rugrigor          #+#    #+#             */
/*   Updated: 2023/11/22 02:19:25 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env2(t_ms *ms, char *oldpwd, int i, int j)
{
	char	**env;

	while (ms->envp[i])
		i++;
	env = malloc(sizeof(char *) * (i + 2));
	if (!env)
		return ;
	i = 0;
	while (ms->envp[i])
	{
		if (ft_strncmp(ms->envp[i], "PWD=", 4) == 0
			&& ft_strncmp(ms->envp[i + 1], "OLDPWD=", 7) == 0)
		{
			free(env);
			return ;
		}
		else if (ft_strncmp(ms->envp[i], "PWD=", 4) == 0)
		{
			env[j++] = ms->envp[i++];
			env[j++] = ft_strjoin("OLD", oldpwd);
		}
		env[j++] = ms->envp[i++];
	}
	env[j] = NULL;
	ms->envp = env;
}

char	*cd2(char *ptr, char *buff, t_ms *ms, int i)
{
	char	*vp;
	int		j;

	j = 0;
	vp = NULL;
	while (ptr[++i])
	{
		if (ptr[i] == '/')
			return (ft_strdup(ptr));
		if (ptr[0] == '-')
		{
			while (ms->envp[j++])
			{
				if (ft_strncmp(ms->envp[j], "OLDPWD=", 7) == 0)
				{
					vp = ms->envp[j] + 7;
					return (vp);
				}
			}
			return (vp);
		}
	}
	if (buff)
		vp = ft_strjoin(buff, (ft_strjoin("/", ptr)));
	else
		return (ptr);
	return (vp);
}

int	ft_chdir(t_ms *ms, char *ptr, int j)
{
	char	*vp;
	char	*buff;

	if (ptr == NULL && ms->tree[ms->ord]->next->_file)
		ptr = ft_strdup(ms->tree[ms->ord]->next->_file);
	else if (ptr == NULL && ms->tree[ms->ord]->next->_word)
		ptr = ft_strdup(ms->tree[ms->ord]->next->_word);
	buff = getcwd(NULL, 0);
	vp = cd2(ptr, buff, ms, -1);
	printf("%s\n", vp);
	chdir(vp);
		// err(NULL, NULL, ms, 4);
	free(buff);
	free(vp);
	// system("leaks minishell");
	env2(ms, ms->envp[j], 0, 0);
	if (ptr && ptr[0] && ptr[0] == '-' && ptr[1] && ptr[1] == '-'
		&& ptr[2] && ptr[2] == '-')
		return (perr("minishell: cd", ms));
	else if (ptr[0] && ptr[0] == '-' && !ptr[1])
		return (pwd(ms, 1));
	else
		return (pwd(ms, 0));
}

int	cd(t_ms *ms, int j)
{
	char	*home;
	char	*ptr;

	goto_start(ms);
	while (ms->envp[++j])
	{
		if (ft_strncmp(ms->envp[j], "HOME=", 5) == 0)
			home = ms->envp[j] + 5;
		if (ft_strncmp(ms->envp[j], "PWD=", 4) == 0)
			break ;
	}
	if (ms->tree[ms->ord]->next == NULL && !ms->tree[ms->ord]->_option)
	{
		if (chdir(home) != 0)
			return (perr("minishell: cd", ms));
		env2(ms, ms->envp[j], 0, 0);
		return (pwd(ms, 0));
	}
	ptr = ft_strdup(ms->tree[ms->ord]->_option);
	ft_chdir(ms, ptr, j);
	free (ptr);
	return (0);
}
