/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:10:20 by rugrigor          #+#    #+#             */
/*   Updated: 2023/01/31 15:25:10 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**number(char const *s, char c)
{
	int		i;
	int		n;
	char	**ptr;

	i = 0;
	n = 0;
	while (s[i])
	{
		if ((s[i] != c && s[i + 1] == c) || (s[i] != c && s[i + 1] == '\0'))
		{
			n++;
			i++;
		}
		else
			i++;
	}
	ptr = (char **)malloc(sizeof(char *) * (n + 1));
	if (ptr == 0)
		return (NULL);
	return (ptr);
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
	return (0);
}

char	**ft_substr1(char **ptr, char c, const char *s, int index)
{
	int	i;
	int	start;
	int	len;

	start = 0;
	i = -1;
	len = 0;
	while (s[++i])
	{
		start = i - len;
		if (s[i] != '\0' && s[i] != c)
		{
			len++;
			if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			{
				ptr[index] = ft_substr(s, start, len);
				if (!ptr[index])
					return (ft_free(&ptr));
				index++;
				len = 0;
			}
		}
	}
	ptr[index] = NULL;
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	if (!s)
		return (NULL);
	return (ft_substr1(number(s, c), c, s, 0));
}
