/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:56:56 by rugrigor          #+#    #+#             */
/*   Updated: 2023/01/31 14:51:44 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *lit, size_t len)
{
	size_t	i;
	char	*big1;
	char	*lit1;

	big1 = (char *)big;
	lit1 = (char *)lit;
	i = 0;
	if (ft_strlen(lit1) == 0)
		return (&big1[i]);
	while (big1 && lit1 && big1[i] && i <= len && len != 0)
	{
		if (big1[i] == lit1[0] && i + ft_strlen(lit1) > len)
			return (NULL);
		else if (big1[i] == lit1[0]
			&& ft_strncmp(&big1[i], &lit1[0], ft_strlen(lit1)) == 0)
			return (&big1[i]);
		i++;
	}
	return (NULL);
}
