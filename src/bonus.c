/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:40:23 by rugrigor          #+#    #+#             */
/*   Updated: 2023/11/10 13:13:42 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_bonus3(char *ptr, int a, int n, int i)
{
	char	str[5000];

	while (ptr[++i] && (ptr[i] != '('
			|| ptr[i] != '|' || ptr[i] != '&'))
		if (ptr[i] == '>' && ptr[i - 1] != '>')
			n = i;
	i = -1;
	while (ptr && ptr[++i])
	{
		a = i + 1;
		if (n < i)
			str[a++] = ptr[i];
		else if (n == i)
		{
			str[i] = ptr[i];
			str[i + 1] = '>';
		}
		else if (n > i)
			str[i] = ptr[i];
	}
	str[a] = '\0';
	ptr = ft_strdup(str);
	return (ptr);
}

char	*hard_bon(t_ms *m, char *ptr, int i, int n)
{
	char	*str;
	char	*str2;

	while (ptr && ptr[++i])
	{
		if (ptr[i] == '(')
		{
			while (ptr && ptr[i++])
			{
				if ((ptr[i] == '&' && ptr[i + 1] == '&')
					|| (ptr[i] == '|' && ptr[i + 1] == '|'))
				{
					n++;
					str = ft_substr(ptr, 0, i - 1);
					str2 = ft_substr(ptr, i - 1, ft_strlen(ptr) - i + 2);
					free(ptr);
					ptr = hard_bon_help(m, n, str, str2);
					i = i + 2 + ft_strlen(m->scope);
					if (n != 1)
						i = i + 2 + ft_strlen(m->scope2);
				}
			}
		}
	}
	return (ptr);
}

void	ft_bonus2(t_ms *m, int i, int a, int n)
{
	char	str[5000];

	while (m->args[++i] && (m->args[i] != '('
			|| m->args[i] != '|' || m->args[i] != '&'))
		if (m->args[i] == '>' && m->args[i - 1] != '>')
			n = i;
	i = -1;
	while (m->args && m->args[++i])
	{
		a = i + 1;
		if (n < i)
			str[a++] = m->args[i];
		else if (n == i)
		{
			str[i] = m->args[i];
			str[i + 1] = '>';
		}
		else if (n > i)
			str[i] = m->args[i];
	}
	str[a] = '\0';
	m->args = hard_bon(m, ft_strdup(str), -1, 0);
}

void	bonus_help(t_ms *m, int x, int n)
{
	n = -1;
	while (m->ptr2[++n])
		if (m->ptr2[n] == '>' || m->ptr2[n] == '<')
			m->prior = 4;
	if (m->prior == 4)
	{
		m->scope = ft_strdup(m->ptr2);
		m->scope2 = ft_bonus3(m->ptr2, -1, -1, -1);
		ft_bonus2(m, x, -1, -1);
	}
	n = -1;
	while (m && m->args && m->args[++n])
		if (m->args[n] == '(')
			while (m->args && m->args[n++] != ')')
				if (m->args[n] == 'e' && (!ft_strncmp(m->args + n, "exit)", 5)
						|| !ft_strncmp(m->args + n, "exit ", 5)))
					m->exit = 5;
}

void	ft_bonus(t_ms *m, int x, int i, int n)
{
	while (m && m->args && m->args[++i])
	{
		if (m->args[i] == '(')
		{
			while (m->args && m->args[i++])
			{
				if ((m->args[i] == '&' && m->args[i + 1] == '&')
					|| (m->args[i] == '|' && m->args[i + 1] == '|'))
				{
					while (m->args && m->args[i++])
					{
						if (m->args[i] == ')')
						{
							x = i;
							while (m->args && m->args[i++] && (m->args[i] != '('
									|| m->args[i] != '|' || m->args[i] != '&'))
								m->ptr2[n++] = m->args[i];
						}
					}
				}
			}
		}
	}
	m->ptr2[n] = '\0';
	bonus_help(m, x, -1);
}
