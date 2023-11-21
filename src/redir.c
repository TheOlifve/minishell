/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:44:07 by rugrigor          #+#    #+#             */
/*   Updated: 2023/11/20 12:30:16 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*read_file(void)
{
	int		file;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	file = open("src/tmp", O_RDONLY);
	tmp2 = ft_strdup("");
	while (1)
	{
		tmp = get_next_line(file);
		if (!tmp)
			break ;
		tmp3 = ft_strjoin(tmp2, tmp);
		free(tmp2);
		tmp2 = ft_strdup(tmp3);
		free(tmp3);
	}
	return (tmp2);
}

int	my_exit(int n, int mod)
{
	if (mod == 0 && (n == 0 || n == 1))
		exit (n);
	else if (mod == 1 && (n == 1 || n < 0))
		exit (1);
	return (0);
}

void	cat_exit(t_ms *ms, char *str)
{
	if (ms->prior == 4)
		ms->prior = 5;
	if (ft_strcmp(str, "/bin/cat") == 0)
	{
		if (g_glob == SIGINT)
			printf("\n");
		if (g_glob == SIGQUIT)
		{
			ms->exit_num = 131;
			printf("Quit: 3\n");
		}
	}
}
