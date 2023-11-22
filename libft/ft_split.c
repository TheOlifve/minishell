/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:37:41 by hrahovha          #+#    #+#             */
/*   Updated: 2023/11/22 23:36:16 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**size(char const *s, char c)
{
	int		i;
	int		len;
	int		cnt;
	char	**mem;

	i = 0;
	cnt = 0;
	len = 0;
	while (i <= (int)ft_strlen(s))
	{
		if (s[i] == c || s[i] == '\0')
		{
			if (len != 0)
				cnt++;
			len = 0;
		}
		else
			len++;
		i++;
	}
	mem = malloc((cnt + 1) * sizeof(char *));
	if (!mem)
		return (NULL);
	mem[cnt] = NULL;
	return (mem);
}

char	**ft_free(char ***str)
{
	int	i;

	i = -1;
	while ((*str)[++i])
	{
		free((*str)[i]);
		(*str)[i] = 0;
	}
	free(*str);
	*str = 0;
	return (NULL);
}

char	**ft_malloc(char const *s, char c, int i, int k)
{
	int		l;
	char	**mem;

	l = 0;
	mem = (char **)size(s, c);
	if (!mem)
		return (NULL);
	while (s[k])
	{
		if (s[k] == c)
			k++;
		else if (s[k] != c)
		{
			l = k;
			while ((s[k] && s[k] != c))
				k++;
			mem[i] = ft_substr(s, l, k - l);
			if (!mem[i])
				return (ft_free(&mem));
			i++;
		}
	}
	return (mem);
}

char	**ft_split(char const *s, char c)
{
	char	**str;

	if (!s)
		return (NULL);
	str = ft_malloc(s, c, 0, 0);
	return (str);
}
