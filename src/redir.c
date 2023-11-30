/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:44:07 by rugrigor          #+#    #+#             */
/*   Updated: 2023/11/30 13:29:46 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	my_write(char *str, int i)
{
	if (i == 0)
	{
		write(2, "minishell: ", 11);
		write(2, str, ft_strlen(str));
		write(2, ": command not found\n", 20);
	}
	else if (i == 1)
	{
		write(2, str, ft_strlen(str));
		write(2, "minishell: Bad file descriptor\n", 31);
	}
	return (-1);
}

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

void	cat_exit(t_ms *ms, char *str)
{
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
