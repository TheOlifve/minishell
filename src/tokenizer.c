/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:32:34 by hrahovha          #+#    #+#             */
/*   Updated: 2023/09/18 22:04:26 by rugrigor         ###   ########.fr       */
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
			m->args_tmp[i + 3] = ' ';
			j += 1;
			i += 3;
		}
		else if (m->args[j] == '|' || m->args[j] == '<' || m->args[j] == '>')
		{
			m->args_tmp[i] = ' ';
			m->args_tmp[i + 1] = m->args[j];
			m->args_tmp[i + 2] = ' ';
			i += 2;
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
		if (m->str[i][0] == '&' || m->str[i][0] == '|')
		{
			(*lexer)->kw = ft_strdup(&m->str[i][0]);
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

void	tokenizer(t_ms *m, t_lexer **lexer)
{	
	//printf("args : %s\n", m->args);
	cnt_for_alloc(m, 0, -1);
	split_by(m, 0, -1);
	m->str = ft_split(m->args_tmp, ' ');
	int i = -1;
	while (m->str[++i])
	//printf("str : %s\n", m->str[i]);
	tabs(m);
	//check_dol(m, 0, -1);
	cnt_for_alloc(m, 1, -1);
	(*lexer) = lstnew();
	while (--m->tok_cnt > 1)
		lstadd_back(lexer, lstnew());
	l_analys(m, lexer);
	pars(*lexer, m);
	engine(m, 0, -1);
	// int	j;

	// j = -1;
	// while (m->lcmd[++j])
	// {
	// 	printf("cmd -  %s\n", m->lcmd[j]->cmd);
	// 	printf("flag - %s\n", m->lcmd[j]->flag);
	// 	printf("file - %s\n", m->lcmd[j]->file);
	// 	printf("f_id - %s\n", m->lcmd[j]->f_id);
	// 	printf("word - %s\n", m->lcmd[j]->word);
	// 	printf("lpp -  %s\n", m->lcmd[j]->lpp);
	// 	printf("lb -   %s\n", m->lcmd[j]->lb);
	// 	printf("tree - %s\n", m->lcmd[j]->tree);
	// 	printf("_______________________________\n");
	// 	m->lcmd[j] = m->lcmd[j]->next;
	// }
	// while (m->lcmd[0])
    // {
    //     printf("%s\n", m->lcmd[0]->cmd);
    //     printf("%s\n", m->lcmd[0]->flag);
    //     printf("%s\n", m->lcmd[0]->file);
    //     printf("%s\n", m->lcmd[0]->f_id);
    //     printf("%s\n", m->lcmd[0]->word);
    //     printf("%s\n", m->lcmd[0]->lpp);
    //     printf("%s\n", m->lcmd[0]->lb);
    //     printf("%s\n", m->lcmd[0]->tree);
    //     m->lcmd[0] = m->lcmd[0]->next;
    // }
    // while (m->lcmd[1])
    // {
    //     printf("%s\n", m->lcmd[1]->cmd);
    //     printf("%s\n", m->lcmd[1]->flag);
    //     printf("%s\n", m->lcmd[1]->file);
    //     printf("%s\n", m->lcmd[1]->f_id);
    //     printf("%s\n", m->lcmd[1]->word);
    //     printf("%s\n", m->lcmd[1]->lpp);
    //     printf("%s\n", m->lcmd[1]->lb);
    //     printf("%s\n", m->lcmd[1]->tree);
    //     m->lcmd[1] = m->lcmd[1]->next;
    // }
    // while (m->lcmd[2])
    // {
    //     printf("%s\n", m->lcmd[2]->cmd);
    //     printf("%s\n", m->lcmd[2]->flag);
    //     printf("%s\n", m->lcmd[2]->file);
    //     printf("%s\n", m->lcmd[2]->f_id);
    //     printf("%s\n", m->lcmd[2]->word);
    //     printf("%s\n", m->lcmd[2]->lpp);
    //     printf("%s\n", m->lcmd[2]->lb);
    //     printf("%s\n", m->lcmd[2]->tree);
    //     m->lcmd[2] = m->lcmd[2]->next;
    // }
	//engine(m, 0, -1);
}
