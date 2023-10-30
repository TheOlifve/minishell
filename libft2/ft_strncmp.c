/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:35:29 by rugrigor          #+#    #+#             */
/*   Updated: 2023/07/24 15:31:33 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s3;
	unsigned char	*s4;
	size_t			i;

	i = 0;
	s3 = (unsigned char *) s1;
	s4 = (unsigned char *) s2;
	if (!s1 || !s2)
		return (0);
	if (n == 0 && s3 == NULL && s4 == NULL)
		return (0);
	while (s3[i] && s4[i] && i < n && s3[i] == s4[i])
		i++;
	if (i < n)
		return (s3[i] - s4[i]);
	else
		return (0);
}
