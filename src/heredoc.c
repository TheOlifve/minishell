/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:32:34 by hrahovha          #+#    #+#             */
/*   Updated: 2023/08/08 18:34:35 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	her_print(void)
{
	int		file;
	char	*tmp;

	file = open("heredoc", O_RDONLY, 0644);
	tmp = get_next_line(file);
	while (tmp)
	{
		printf("%s", tmp);
		free(tmp);
		tmp = get_next_line(file);
	}
	close(file);
	free(tmp);
}

int	heredoc(char *str)
{
	int		file;
	char	*tmp;

	file = open("heredoc", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (file < 0)
		return (1);
	while (1)
	{
		write(1, "heredoc> ", 9);
		tmp = get_next_line(0);
		if (!tmp)
			break ;
		if (ft_strcmp(str, tmp) == -10)
			break ;
		write(file, tmp, ft_strlen(tmp));
		free(tmp);
	}
	close(file);
	free(tmp);
	her_print();
	unlink("heredoc");
	return (0);
}

int	redir(char *str)
{
	int		file;
	char	*tmp;

	file = open(str, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (file < 0)
		return (1);
	tmp = get_next_line(0);
	while (tmp)
	{
		write(file, tmp, ft_strlen(tmp));
		free(tmp);
		tmp = get_next_line(0);
	}
	free(tmp);
	close(file);
	return (0);
}

int	redir_append(char *str)
{
	int		file;
	char	*tmp;

	file = open(str, O_RDWR | O_APPEND | O_CREAT, 0644);
	if (file < 0)
		return (1);
	tmp = get_next_line(0);
	while (tmp)
	{
		write(file, tmp, ft_strlen(tmp));
		free(tmp);
		tmp = get_next_line(0);
	}
	free(tmp);
	close(file);
	return (0);
}