/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:44:07 by rugrigor          #+#    #+#             */
/*   Updated: 2023/12/20 14:25:09 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env2(t_ms *ms, char **env, int i, int j)
{
	while (ms->envp[i])
		i++;
	env = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (ms->envp[i])
	{
		if (ft_strncmp(ms->envp[i], "PWD=", 4) == 0
			&& ft_strncmp(ms->envp[i + 1], "OLDPWD=", 7) == 0)
		{
			env[j] = NULL;
			doublefree(env);
			return ;
		}
		else if (ft_strncmp(ms->envp[i], "PWD=", 4) == 0)
		{
			env[j++] = ft_strdup(ms->envp[i++]);
			env[j++] = ft_strjoin("OLD", ms->envp[i - 1]);
		}
		env[j++] = ft_strdup(ms->envp[i++]);
	}
	env[j] = NULL;
	doublefree(ms->envp);
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
	return (cd2_help(vp, ptr, buff, NULL));
}

int	ft_chdir3(t_ms *ms, char *ptr)
{
	if (ptr != NULL && ptr[0] && ptr[0] == '-' && ptr[1] && ptr[1] == '-'
		&& ptr[2] && ptr[2] == '-')
	{
		free (ptr);
		return (perr("minishell: cd", ms));
	}
	else if (ptr != NULL && ptr[0] && ptr[0] == '-' && !ptr[1])
	{
		free (ptr);
		return (pwd(ms, 2, -1, NULL));
	}
	else
	{
		free(ptr);
		return (pwd(ms, 0, -1, NULL));
	}
	return (0);
}

int	ft_chdir(t_ms *ms, char *ptr, char *vp, int i)
{
	char	*buff;

	buff = getcwd(NULL, 0);
	if (buff == NULL)
		chdir4(ms);
	if ((ptr == NULL && ms->tree[ms->ord]->next->_file)
		|| (ptr == NULL && ms->tree[ms->ord]->next->_word))
		free(ptr);
	if (ptr == NULL && ms->tree[ms->ord]->next->_file)
		ptr = ft_strdup(ms->tree[ms->ord]->next->_file);
	else if (ptr == NULL && ms->tree[ms->ord]->next->_word)
		ptr = ft_strdup(ms->tree[ms->ord]->next->_word);
	vp = cd2(ptr, buff, ms, -1);
	free(buff);
	while (ms->envp[i])
		i++;
	if (chdir(vp) != 0)
		return (ft_chdir2(ms, ptr, vp));
	env2(ms, NULL, i, 0);
	if (ptr && ptr[0] && !(ptr[0] == '-'))
		free(vp);
	return (ft_chdir3(ms, ptr));
}

int	cd(t_ms *ms, int j)
{
	char	*home;
	char	*ptr;

	goto_start(ms);
	while (ms->envp[++j])
		if (ft_strncmp(ms->envp[j], "HOME=", 5) == 0)
			home = ms->envp[j] + 5;
	if (ms->tree[ms->ord]->next == NULL && !ms->tree[ms->ord]->_option)
	{
		if (chdir(home) != 0)
			return (perr("minishell: cd", ms));
		env2(ms, NULL, 0, 0);
		return (pwd(ms, 0, -1, NULL));
	}
	ptr = ft_strdup(ms->tree[ms->ord]->_option);
	ft_chdir(ms, ptr, NULL, 0);
	return (0);
}
