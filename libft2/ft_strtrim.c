/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:38:58 by rugrigor          #+#    #+#             */
/*   Updated: 2023/01/31 14:54:56 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*part1(char *s1, char *set)
{
	int		ptr[128];
	size_t	i;

	i = 0;
	while (i < 128)
		ptr[i++] = 0;
	i = 0;
	while (i < (ft_strlen(set)))
	{
		if (ptr[(int)set[i]] == 0)
			ptr[(int)set[i]] = 1;
		i++;
	}
	i = 0;
	while (s1[i])
	{
		if (ptr[(int)s1[i]] == 0)
			return (&s1[i]);
		i++;
	}
	return (NULL);
}

char	*part2(char *s1, char *set, int i, int n)
{
	int		ptr[128];
	char	*ptr1;

	while (i < 128)
		ptr[i++] = 0;
	i = 0;
	if (!s1)
		return (ft_strdup(""));
	while ((size_t)i < (ft_strlen(set)))
	{
		if (ptr[(int)set[i]] == 0)
			ptr[(int)set[i]] = 1;
		i++;
	}
	n = (unsigned int)ft_strlen(s1) - 1;
	while (s1[n] && ptr[(int)s1[n]] != 0)
		--n;
	i = -1;
	ptr1 = malloc(sizeof(char) * (n + 2));
	if (!ptr1)
		return (NULL);
	while (++i <= n)
		ptr1[i] = s1[i];
	ptr1[i] = '\0';
	return (&*ptr1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	ptr = part1((char *)s1, (char *)set);
	return (part2(ptr, (char *)set, 0, 0));
}
