/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:02:35 by rugrigor          #+#    #+#             */
/*   Updated: 2023/09/08 13:33:26 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <libft.h>
# include <sys/stat.h>
# include <signal.h>
# include <sys/ioctl.h>

# define STDIN 0
# define STDOUT 1

typedef struct s_lexer
{
	char			*kw;
	char			*id;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}				t_lexer;

typedef struct s_lcmd
{
	char			*lb;
	char			*lpp;
	char			*cmd;
	char			*tree;
	char			*flag;
	char			*file;
	char			*f_id;
	char			*word;
	struct s_lcmd	*next;
	struct s_lcmd	*prev;
}				t_lcmd;

typedef struct s_pipex
{
	pid_t	pid;
	int		**fd;
	int		file1;
	int		file2;
	int		cmd_crnt;
	int		cmd_cnt;
	int		pipes_cnt;
	int		here_doc;
	int		index;
	int		p_argc;
	char	**path;
	char	*cmd;
}t_pipex;

typedef struct s_ms
{
	int		a;
	int		i;
	int		f;
	int		n;
	int		x;
	int		pp;
	int		bb;
	int		c1;
	int		c2;
	int		in;
	int		out;
	int		num;
	int		pos;
	int		dol;
	int		cmd;
	int		fd[2];
	int		cache;
	int		index;
	int		error;
	int		tok_cnt;
	int		builtins;
	int		dol_check;
	char	*ft2;
	char	*ptr;
	char	*path;
	char	*args;
	char	**str;
	char	**envp;
	char	**envp1;
	char	*wd_tmp;
	char	*ex_tmp;
	char	*us_tmp;
	char	**p_argv;
	char	*args_tmp;
	char	*args_old;
	t_lcmd	*lcmd[OPEN_MAX];
}				t_ms;

int		env(t_ms *ms);
int		redir(char *str);
int		heredoc(char *str);
int		eng(t_ms *ms, int i);
int		chak(t_ms *ms, int i);
int		pwd(t_ms *ms, int mod);
int		redir_append(char *str);
int		simbol(t_ms *ms, int i);
int		perr(char *str, t_ms *ms);
int		cd(t_ms *ms, int i, int j);
int		exit_mode(int n, t_ms *ms);
int		cmd(t_ms *ms, char **envp);
int		dol_count(char *str, int i);
int		wildcard(t_ms *ms, char *str);
int		ft_unset(t_ms *ms, char *str);
int		engine(t_ms *ms, int i, int n);
int		get_cmd(char *path, char *cmd);
int		ft_export(t_ms *ms, char *str);
int		echo(t_ms *ms, int i, int flag);
int		str_join(t_ms *ms, int i, char c);
int		help(char *lex, t_ms *ms, int i, char *ptr);
int		pipex(t_ms *ms, int i, char **argv, int	num);
int		help_helper(char *join, char *ptr, char *lex, t_ms *ms);
char	**path_x(char **envp);
char	*get_next_line(int fd);
char	*dol_check(t_ms *ms, char *ptr);
char	*check_ft(t_ms *ms, char *ft, int i);
char	*ft_join(char *str, char *str2, int i);
char	*dol2(char *ptr, char *str, int i, int n);
char	*slash(t_ms *ms, char *ptr, int i);
char	*cmd_builder(t_ms *ms, int i, char *tmp, char *cmd);
void	home(void);
void	navak1(void);
void	navak2(void);
void	sig2(int sig);
void	new7(t_ms *ms);
void	new1(t_lcmd *new);
void	ft_free2(t_ms *ms);
void	ft_search(t_ms *ms);
void	prior(t_lexer *lex);
void	exec_cmd(t_ms *ms, int i);
void	pipe_close(t_pipex *pipex);
void	ctrld(char *line, t_ms *ms);
void	pars(t_lexer *lex, t_ms *ms);
void	path(t_ms *ms, int i, int n);
void	loop(t_ms *m_s, t_lexer *lexer);
void	infos3(t_lcmd *new, char **info);
void	check_dol(t_ms *ms, int	i, int j);
void	tokenizer(t_ms *m, t_lexer **lexer);
void	ft_dup2(int read, int write, t_ms *ms);
void	lstadd_back(t_lexer **lst, t_lexer *new);
void	lcmd_add_back(t_lcmd **tree, char **info, t_ms *ms);
void	child_help(t_pipex *pipex, t_ms *ms, char **cmd_args, int j);
t_lexer	*lstnew(void);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

#endif