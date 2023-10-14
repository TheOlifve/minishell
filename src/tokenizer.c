/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:32:34 by hrahovha          #+#    #+#             */
/*   Updated: 2023/09/22 15:28:36 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cnt_for_alloc(t_ms *m, int k, int i)
{
	int	j;

	if (k == 0)
	{	
		j = ft_strlen(m->args);
		while (m->args && m->args[++i])
		{
			if ((m->args[i] == '>' && m->args[i + 1] == '>')
				|| (m->args[i] == '<' && m->args[i + 1] == '<'))
					i += 1;
			if (m->args[i] == '|' || m->args[i] == '<' || m->args[i] == '>')
					j += 2;
		}
		j += 1;
		m->args_tmp = malloc(j * sizeof(char *));
	}
	else
	{
		while (m->str && m->str[++i])
			;
		i += 1;
		m->tok_cnt = i;
	}
}

void	split_by(t_ms *m, int i, int j)
{
	while (m->args && m->args[++j])
	{
		if ((m->args[j] == '>' && m->args[j + 1] == '>')
			|| (m->args[j] == '<' && m->args[j + 1] == '<'))
		{
			m->args_tmp[i] = ' ';
			m->args_tmp[i + 1] = m->args[j];
			m->args_tmp[i + 2] = m->args[j];
			j += 1;
			i += 2;
		}
		else if (m->args[j] == '<' || m->args[j] == '>')
		{
			m->args_tmp[i] = ' ';
			m->args_tmp[i + 1] = m->args[j];
			i += 1;
		}
		else if (m->args[j] == '|' && m->args[j + 1] != '|')
		{
			m->args_tmp[i] = ' ';
			m->args_tmp[i + 1] = m->args[j];
			m->args_tmp[i + 2] = ' ';
			i += 2;
		}
		else if (m->args[j] == '|')
		{
			m->args_tmp[i] = ' ';
			m->args_tmp[i + 1] = m->args[j];
			m->args_tmp[i + 2] = m->args[j];
			m->args_tmp[i + 3] = ' ';
			i += 3;
			j += 1;
		}
		else
			m->args_tmp[i] = m->args[j];
		i += 1;
	}
	m->args_tmp[i] = '\0';
}

void	l_analys(t_ms *m, t_lexer **lexer)
{
	int		i;
	t_lexer	*head;

	i = -1;
	head = *lexer;
	while (m->str && m->str[++i] && *lexer)
	{
		if (m->str[i][0] == '&' || m->str[i][0] == '|'
			|| m->str[i][0] == '>' || m->str[i][0] == '<')
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

void	tabs(t_ms *m)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (m && m->str && m->str[++i])
	{
		j = -1;
		while (m->str[i][++j])
		{
			if (m->str[i][j] == 5 || m->str[i][j] == ';')
				m->str[i][j] = 32;
			if (m->str[i][j] == 4)
				m->str[i][j] = '\t';
		}
	}
}

int	check_tabs(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == 9 || str[i] == 32)
			i++;
		else
			return (0);
	}
	return (1);
}

int	tokenizer(t_ms *m, t_lexer **lexer)
{	
	cnt_for_alloc(m, 0, -1);
	split_by(m, 0, -1);
	m->str = ft_split(m->args_tmp, ' ');
	if (check_tabs(m->args_tmp) == 1)
		return(0);
	tabs(m);
	//check_dol(m, 0, -1);
	cnt_for_alloc(m, 1, -1);
	(*lexer) = lstnew();
	while (--m->tok_cnt > 1)
		lstadd_back(lexer, lstnew());
	l_analys(m, lexer);
	parser(*lexer, m);
	engine(m);
	return (0);
}
