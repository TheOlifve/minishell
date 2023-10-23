/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:02:35 by rugrigor          #+#    #+#             */
/*   Updated: 2023/10/19 15:23:27 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
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

// typedef struct s_lcmd
// {
// 	char			*lb;
// 	char			*lpp;
// 	char			*cmd;
// 	char			*tree;
// 	char			*flag;
// 	char			*file;
// 	char			*f_id;
// 	char			*word;
// 	struct s_lcmd	*next;
// 	struct s_lcmd	*prev;
// }				t_lcmd;

typedef struct s_tree
{
	char			*_cmd;
	char			*_option;
	char			*_redir;
	char			*_file;
	char			*_word;
	char			*_pipe;
	char			*_and;
	char			*_or;
	struct s_tree	*next;
	struct s_tree	*prev;
}				t_tree;

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
	int		x;
	int		c1;
	int		c2;
	int		num;
	int		dol;
	int		ord;
	int		err;
	int		dol2;
	int		fd[2];
	int		p_err;
	int		exit_num;
	int		bool_word;
	int		save_stdout;
	char	*ptr;
	char	*path;
	char	*args;
	char	**str;
	char	**envp;
	char	*wd_tmp;
	char	*args_old;
	t_tree	*tree[OPEN_MAX];
	// int		a;
	// int		i;
	// int		f;
	// int		n;
	// int		pp;
	// int		bb;
	// int		in;
	// int		out;
	// int		pos;
	// int		cmd;
	// int		free;
	// int		index;
	// int		tok_cnt;
	// int		builtins;
	// int		dol_check;
	// int		exit_error;
	// char	**cache;
	// char	*ex_tmp;
	// char	*us_tmp;
	// char	**p_argv;
	// char	*args_tmp;
	// t_lcmd	*lcmd[OPEN_MAX];
}				t_ms;

int		env(t_ms *ms);
int		engine(t_ms *ms);
int		heredoc(char *str);
int		cd(t_ms *ms, int j);
int		pwd(t_ms *ms, int mod);
int		simbol(t_ms *ms, int i);
int		echo(t_ms *ms, int flag);
int		perr(char *str, t_ms *ms);
int		exec_with_redir(t_ms *ms);
int		exit_mode(int n, t_ms *ms);
int		dol_count(char *str, int i);
int		check_var(char *str, t_ms *ms);
int		wildcard(t_ms *ms, char *str);
int		redir(char *str, char **str2);
int		redir_after_exec(char **file);
int		get_cmd(char *path, char *cmd);
int		exec_cmd(t_ms *ms, char	**cmd);
int		cmd_find(t_ms *ms, char **cmd);
int		pars_err(char *error, t_ms *ms);
int		parser(t_lexer *lexer, t_ms *ms);
int		o_space2(t_ms *ms, int i, int n);
int		o_space3(t_ms *ms, int i, int n);
int		ft_export3(t_ms *ms, int i, int j);
int		ERR(char *error, char *str, t_ms *ms);
int		ft_unset(t_ms *ms, char **str, int i);
int		ft_export(t_ms *ms, char **str, int i);
int		dol_prep(t_ms *ms, int i, int x, int y);
int		ft_export2(t_ms *ms, char **str, int i);
int		pipex(t_ms *ms, char **argv, int	num);
int		operator_distribute(t_ms *ms, char *opr);
int		word_distribute(t_lexer **lexer, t_ms *ms, char *word);
char	*read_file(void);
char	**caching(char **str);
char	**path_x(char **envp);
char	*get_next_line(int fd);
char	*cmd_builder(t_ms *ms);
char	*dol_check(t_ms *ms, char *ptr);
char	*cmd_build(t_ms *ms, char *word);
char	*ft_concat(char *cmd, char *opt);
char	**ft_masjoin(char **tmp, char *str);
char	*ft_join(char *str, char *str2, int i);
char	*dol2(char *ptr, char *str, int i, int n);
void	navak1(void);
void	navak2(void);
void	sig2(int sig);
void	ft_free2(t_ms *ms);
void	goto_start(t_ms *ms);
void	tabzz(t_ms *ms, int i);
void	open_files(char **file);
void	pipe_close(t_pipex *pipex);
void	ctrld(char *line, t_ms *ms);
void	ft_dup2(int read, int write, t_ms *ms);
void	lstadd_back(t_lexer **lst, t_lexer *new);
void	tree_add_back(t_tree **tree, t_tree *new);
void	tokenizer(t_ms *m, t_lexer **lexer, int i, int j);
void	child_help(t_pipex *pipex, t_ms *ms, char **cmd_args, int j);
t_lexer	*lstnew(void);
t_tree	*tree_new(void);
// int		eng(t_ms *ms, int i);
// int		chak(t_ms *ms, int i);
// int		redir_append(char *str);
// int		redir_loop(t_ms *ms);
// int		cmd(t_ms *ms, char **envp);
// int		str_join(t_ms *ms, int i, char c);
// int		help(char *lex, t_ms *ms, int i, char *ptr);
// int		help_helper(char *join, char *ptr, char *lex, t_ms *ms);
// char	*check_ft(t_ms *ms, char *ft, int i);
// char	*slash(t_ms *ms, char *ptr, int i);
// void	home(void);
// void	new7(t_ms *ms);
// void	new1(t_lcmd *new);
// void	ft_search(t_ms *ms);
// void	prior(t_lexer *lex);
// void	pars(t_lexer *lex, t_ms *ms);
// void	path(t_ms *ms, int i, int n);
// int		loop(t_ms *m_s, t_lexer *lexer);
// int		redir_input(t_ms *ms);
// void	infos3(t_lcmd *new, char **info);
// void	check_dol(t_ms *ms, int	i, int j);
// void	lcmd_add_back(t_lcmd **tree, char **info, t_ms *ms);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

#endif