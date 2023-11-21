/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:44:07 by rugrigor          #+#    #+#             */
/*   Updated: 2023/11/17 20:50:58 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	my_write(char *str)
{
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, ": command not found\n", 20);
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
			break;
		tmp3 = ft_strjoin(tmp2, tmp);
		free(tmp2);
		tmp2 = ft_strdup(tmp3);
		free(tmp3);
	}
	return (tmp2);
}

void	redir_dup(int fd2, char *str)
{
	int	i;
	int	fd;
	
	fd = open("src/tmp", O_RDWR | O_TRUNC | O_CREAT, 0644);
	i = ft_last(ft_split(str, ' '));
	if (fd2 >= 0 && i == -3)
		dup2(open("src/heredoc", O_RDWR), 0);
	else if (fd2 >= 0 && i == -2)
		dup2(fd2, 0);
	if (i >= 0)
		dup2(fd, 1);
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
