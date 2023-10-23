/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:32:34 by hrahovha          #+#    #+#             */
/*   Updated: 2023/10/19 15:12:43 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	o_space3(t_ms *ms, int i, int n)
{
	char	*str1;
	char	*str2;
	int x;
	
	x = 0;
	i = i + n;
	str1 = ft_substr(ms->args_old, 0, i);
	while (ms->args_old[i] == ' ')
	{
		i++;
		x++;
	}
	str2 = ft_substr(ms->args_old,
			i, ft_strlen(ms->args_old) - i);
	free(ms->args_old);
	ms->args_old = ft_strjoin(str1, str2);
	ms->num -= x;
	return (0);
}

int	o_space2(t_ms *ms, int i, int n)
{
	char	*str1;
	char	*str2;
	
	if (i != 0 && ms->args_old[i] == '|' && ms->args_old[i + 1] == '|'
		&& ms->args_old[i + 2] == 32 && ms->args_old[i - 1] == 32)
		return (3);
	i = i + n;
	str1 = ft_strjoin(ft_substr(ms->args_old, 0, i), " ");
	str2 = ft_substr(ms->args_old,
			i , ft_strlen(ms->args_old) - i);
	free(ms->args_old);
	ms->args_old = ft_strjoin(str1, str2);
	ms->num++;
	return (1);
}

void	l_analys(t_ms *m, t_lexer **lexer)
{
	int		i;
	t_lexer	*head;

	i = -1;
	head = *lexer;
	while (m->str && m->str[++i] && *lexer)
	{
		if ((m->str[i][0] == '&' && m->str[i][1] == '&')|| m->str[i][0] == '|'
			|| m->str[i][0] == '>' || m->str[i][0] == '<'
			|| (m->str[i][0] == '|' && m->str[i][1] == '|'))
		{
			(*lexer)->kw = ft_strdup(m->str[i]);
			(*lexer)->id = ft_strdup("operator\0");
		}
		else
		{
			(*lexer)->id = ft_strdup("word\0");
			(*lexer)->kw = ft_strdup(m->str[i]);
		}
		if ((*lexer)->next)
			*lexer = (*lexer)->next;
	}
	(*lexer) = head;
}

void	tokenizer(t_ms *m, t_lexer **lexer, int i , int j)
{
	m->str = ft_split(m->args, ' ');
	while (m && m->str && m->str[++i])
	{
		j = -1;
		while (m->str[i][++j])
		{
			if (m->str[i][j] == 5)
				m->str[i][j] = 32;
			if (m->str[i][j] == 4)
				m->str[i][j] = '\t';
		}
	}
	(*lexer) = lstnew();
	while (i-- > 1)
		lstadd_back(lexer, lstnew());
	l_analys(m, lexer);
	while ((*lexer)->prev)
		*lexer = (*lexer)->prev;
	parser(*lexer, m);
	if (m->p_err == 0)
		engine(m);
}
