/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:44:07 by rugrigor          #+#    #+#             */
/*   Updated: 2023/11/10 14:12:59 by hrahovha         ###   ########.fr       */
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

int	exec_with_redir2(t_ms *ms, char **cmd, int pid, int fd2)
{
	int	i;
	int	fd;
	int	ptr[1];

	fd = open("src/tmp", O_RDWR | O_TRUNC | O_CREAT, 0644);
	pid = fork();
	if (pid == 0)
	{
		if (fd2 >= 0)
			dup2(fd2, 0);
		if (ft_last(ft_split(ms->tree[ms->ord]->_redir, ' ')) >= 0)
			dup2(fd, 1);
		
		i = cmd_find(ms, cmd);
		exec_with_redir_pipe3(i);
		execve (cmd[0], cmd, ms->envp);
		exit_mode(7, ms);
	}
	while (wait(ptr) != -1)
		;
	return (ptr[0]);
}

int	redir(char *str, char **str2)
{
	int		i;
	int		fd;
	char	*file;

	fd = 0;
	i = ft_last(str2);
	if (i == -1)
		return (1);
	file = str2[i];
	if (ft_strncmp(file, ">>", 2) == 0 && file != NULL)
	{
		file += 2;
		fd = open(file, O_RDWR | O_APPEND | O_CREAT, 0644);
	}
	else if (ft_strncmp(file, ">", 1) == 0 && file != NULL)
	{
		file += 1;
		fd = open(file, O_RDWR | O_TRUNC | O_CREAT, 0644);
	}
	write(fd, str, ft_strlen(str));
	close(fd);
	if (fd < 0)
		return (1);
	return (0);
}

int	redir_loop(t_ms *ms)
{
	char	*_read;
	char	*tmp;
	char	*tmp2;
	char	**file;

	tmp2 = ft_strdup("");
	while (1)
	{
		_read = get_next_line(0);
		if (!_read)
			break ;
		tmp = ft_strjoin(tmp2, _read);
		free(tmp2);
		tmp2 = ft_strdup(tmp);
		free(tmp);
	}
	file = ft_split(ms->tree[ms->ord]->_redir, ' ');
	if (redir(tmp2, file) == 1)
	{
		free(file);
		free(tmp2);
		return (1);
	}
	free(tmp2);
	return (0);
}

int	exec_with_redir(t_ms *ms, int fd)
{
	int		pid;
	int		ptr;
	char	*file;
	char	**cmd;

	if (!ms->tree[ms->ord]->_cmd && ms->tree[ms->ord]->_redir)
		return (open_files(ft_split(ms->tree[ms->ord]->_redir, ' '), -1));
	file = ft_strdup(ms->tree[ms->ord]->_redir);
	fd = open_files(ft_split(file, ' '), -1);
	if (fd == -2)
		return (1);
	cmd = ft_split(cmd_builder(ms), ' ');
	pid = 0;
	ptr = exec_with_redir2(ms, cmd, pid, fd);
	if (ptr > 0)
	{
		unlink("src/tmp");
		return (1);
	}
	redir(read_file(), ft_split(file, ' '));
	unlink("src/tmp");
	return (0);
}
