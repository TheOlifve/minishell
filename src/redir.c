/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:44:07 by rugrigor          #+#    #+#             */
/*   Updated: 2023/11/11 10:42:08 by rugrigor         ###   ########.fr       */
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
			break;
		tmp3 = ft_strjoin(tmp2, tmp);
		free(tmp2);
		tmp2 = ft_strdup(tmp3);
		free(tmp3);
	}
	return (tmp2);
}

void	redir_dup(t_ms *ms, int fd2)
{
	int	i;
	int	fd;
	
	fd = open("src/tmp", O_RDWR | O_TRUNC | O_CREAT, 0644);
	i = ft_last(ft_split(ms->tree[ms->ord]->_redir, ' '));
	if (fd2 >= 0 && i == -3)
		dup2(open("src/heredoc", O_RDWR), 0);
	else if (fd2 >= 0 && i == -2)
		dup2(fd2, 0);
	if (i >= 0)
		dup2(fd, 1);
}

int	exec_with_redir2(t_ms *ms, char **cmd, int pid, int fd2)
{
	int	i;
	int	ptr[1];

	pid = fork();
	if (pid == 0)
	{
		redir_dup(ms, fd2);
		i = cmd_find(ms, cmd);
		if (i == 0)
			exit(0);
		else if (i == 1)
		{
			printf("minishell: error\n");
			exit(1);
		}
		execve (cmd[0], cmd, ms->envp);
		exit_mode(7, ms);
	}
	while (wait(ptr) != -1)
		;
	ms->exit_num = ptr[0];
	return (ptr[0]);
}

int	redir(char *str, char **str2)
{
	int		i;
	int		fd;
	char	*file;

	fd = 0;
	i = ft_last(str2);
	if (i < 0)
		return (1);
	file = ft_strdup(str2[i]);
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

int	exec_with_redir(t_ms *ms, int fd)
{
	int		pid;
	int		ptr;
	char	*file;
	char	**cmd;

	if (!ms->tree[ms->ord]->_cmd && ms->tree[ms->ord]->_redir)
		return (open_files(ms, ft_split(ms->tree[ms->ord]->_redir, ' '), fd));
	file = ft_strdup(ms->tree[ms->ord]->_redir);
	fd = open_files(ms, ft_split(file, ' '), fd);
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
