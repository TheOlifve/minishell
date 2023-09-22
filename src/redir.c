/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:44:07 by rugrigor          #+#    #+#             */
/*   Updated: 2023/09/07 22:33:34 by rugrigor         ###   ########.fr       */
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

int	exec_with_redir2(t_ms *ms, char **cmd, int pid)
{
	int	i;
	int	fd;
	int	ptr[1];

	fd = open("src/tmp", O_RDWR | O_TRUNC | O_CREAT, 0644);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd, 1);
		i = cmd_find(ms, cmd);
		if (i == 0)
			exit(0);
		else if (i == 1)
		{
			printf("minishell: error\n");
			exit(1);
		}
		execve (cmd[0], cmd, ms->envp);
		dup2(1, STDOUT);
		printf("minishell: %s: command not found\n", cmd[0]);
		exit_mode(7, ms);
	}
	while (wait(ptr) != -1)
		;
	return (ptr[0]);
}

// int	exec_with_redir2(t_ms *ms, char **cmd, char *file)
// {
// 	int		pid;
// 	int		ptr;

// 	pid = 0;
// 	ptr = exec_with_redir3(ms, cmd, pid);
// 	if (ptr > 0)
// 	{
// 		open_files(ft_split(file, ' '));
// 		return (1);
// 	}
// 	redir(read_file(), ft_split(file, ' '));
// 	return (0);
// }

int	exec_with_redir(t_ms *ms)
{
	int		pid;
	int		ptr;
	char	*file;
	char	**cmd;
	
	(void)cmd;
	if (!ms->tree[ms->ord]->_cmd && ms->tree[ms->ord]->_redir)
	{
		redir_loop(ms);
		return (0);
	}
	file = ft_strdup(ms->tree[ms->ord]->_redir);
	cmd = cmd_builder(ms);
	pid = 0;
	ptr = exec_with_redir2(ms, cmd, pid);
	if (ptr > 0)
	{
		open_files(ft_split(file, ' '));
		unlink("src/tmp");
		return (1);
	}
	redir(read_file(), ft_split(file, ' '));
	unlink("src/tmp");
	return (0);
}
