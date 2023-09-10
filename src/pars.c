/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:17:31 by rugrigor          #+#    #+#             */
/*   Updated: 2023/09/06 14:51:25 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	op(t_lexer *lex, t_ms *ms, t_lcmd **lcmd)
{
	if ((lex->kw && lex->next && lex->next->kw
		&& lex->kw[0] == '|' && lex->next->kw[0] != '|')
		|| (lex->kw && !lex->next && lex->kw[0] == '|'))
	{
		(*lcmd)->lpp = "+";
		if (lex->next)
			lex = lex->next;
	}
	else if (lex->kw && lex->kw[0] == '&' && lex->kw[1] == '&')
	{
		(*lcmd)->lb = "+";
		if (lex->next)
			lex = lex->next;
	}
	else if (lex->kw && lex->next && lex->next->kw
		&& lex->kw[0] == '|' && lex->next->kw[0] == '|')
	{
		(*lcmd)->tree = "+";
		if (lex->next->next)
			lex = lex->next->next;
	}
	pars(lex, ms);
}

char	*flag(t_lexer *lex, t_ms *ms)
{
	char	*ptr;
	char	*str;

	ptr = NULL;
	if (lex->next)
		lex = lex->next;
	ms->f = 0;
	while (lex->kw && lex->kw[0] == '-' && ft_isalpha(lex->kw[1]) == 1)
	{
		ms->f++;
		if (!ptr)
			ptr = lex->kw;
		else
		{
			str = ptr;
			ptr = ft_strjoin(str, ft_strtrim(lex->kw, "-"));
		}
		if (lex->next)
			lex = lex->next;
		else
			break ;
	}
	return (ptr);
}

int	help(char *lex, t_ms *ms, int i, char *ptr)
{
	char	*join;
	char	**str;

	str = ft_split(ms->path, ':');
	join = ft_strjoin("/", lex);
	while (str && str[++i])
	{
		free(ptr);
		ptr = ft_strjoin(str[i], join);
		if (access(ptr, X_OK) == 0)
			return (help_helper(join, ptr, lex, ms));
		if (ft_strncmp(lex, "./", 2) == 0)
		{
			ms->ptr = lex;
			return (1);
		}
		if (ft_strncmp(lex, "./", 2) == 0)
		{
			ms->ptr = lex;
			return (1);
		}
	}
	free(ptr);
	free(join);
	return (0);
}

char	**word(t_lexer *lex, t_ms *ms, char **ptr)
{
	ptr = malloc(sizeof(char *) * 3);
	if (!ptr)
		return (NULL);
	if (lex->kw[0] == '>' || lex->kw[0] == '<')
	{
		if (lex->kw[1] == '>' || lex->kw[1] == '<')
			ptr[1] = ft_strdup(ft_strjoin(&lex->kw[0], &lex->kw[1]));
		else
			ptr[1] = ft_strdup(&lex->kw[0]);
		lex = lex->next;
		ptr[0] = lex->kw;
	}
	else if (help(lex->kw, ms, -1, NULL) != 0)
	{
		ptr[0] = lex->kw;
		ptr[1] = flag(lex, ms);
	}
	else
	{
		ptr[0] = lex->kw;
		ptr[1] = NULL;
	}
	ptr[2] = NULL;
	return (ptr);
}

void	pars(t_lexer *lex, t_ms *ms)
{
	t_lcmd	*lcmd;

	lcmd = NULL;
	ms->lcmd[ms->i] = lcmd;
	while (lex)
	{
		//prior(lex);
		if (lex->id && lex->id[0] == 'w')
			lcmd_add_back(&lcmd, (word(lex, ms, NULL)), ms);
		else if (lex->id && lex->id[0] == 'o')
		{
			op(lex, ms, &lcmd);
			break ;
		}
		if (lex->kw && (lex->kw[0] == '>' || lex->kw[0] == '<'))
			lex = lex->next;
		if (ms->f != 0)
			while (ms->f != 0)
			{
				if (lex->next)
					lex = lex->next;
				ms->f--;
			}
		lex = lex->next;
	}
}
