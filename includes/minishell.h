/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:02:35 by rugrigor          #+#    #+#             */
/*   Updated: 2023/11/20 12:43:28 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <limits.h>
# include <stdarg.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define STDIN 0
# define STDOUT 1

typedef struct s_lexer
{
	char			*kw;
	char			*id;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}				t_lexer;

typedef struct s_tree
{
	char			*_or;
	char			*_cmd;
	char			*_and;
	char			*_file;
	char			*_word;
	char			*_pipe;
	char			*_redir;
	char			*_option;
	struct s_tree	*next;
	struct s_tree	*prev;
}				t_tree;

typedef struct s_pipex
{
	pid_t	pid;
	int		**fd;
	int		file1;
	int		file2;
	int		index;
	int		p_argc;
	int		cmd_cnt;
	int		cmd_crnt;
	int		here_doc;
	int		pipes_cnt;
	char	*cmd;
	char	**path;
}t_pipex;

typedef struct s_ms
{
	int		x;
	int		c1;
	int		c2;
	int		bb;
	int		num;
	int		dol;
	int		ord;
	int		err;
	int		dol2;
	int		exit;
	int		fd[2];
	int		p_err;
	int		index;
	int		prior;
	int		bonus;
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
	struct sigaction	sa;
}				t_ms;

int		eng(t_ms *ms);
int		env(t_ms *ms);
int		handler(void);
int		handler2(void);
int		cd(t_ms *ms, int j);
int		check_var2(char *str);
int		pwd(t_ms *ms, int mod);
int		spaces(t_ms *ms, int i);
int		engine(t_ms *ms, int n);
int		my_exit(int n, int mod);
int		simbol(t_ms *ms, int i);
int		echo(t_ms *ms, int flag);
int		perr(char *str, t_ms *ms);
int		exit_mode(int n, t_ms *ms);
int		dol_count(char *str, int i);
int		tabzz(t_ms *ms, int i, int c);
int		wildcard(t_ms *ms, char *str);
int		check_var(char *str, t_ms *ms);
int		get_cmd(char *path, char *cmd);
int		cmd_find(t_ms *ms, char **cmd);
int		std_dup(t_ms *ms, char **file);
int		pars_err(char *error, t_ms *ms);
int		parser(t_lexer *lexer, t_ms *ms);
int		o_space2(t_ms *ms, int i, int n);
int		o_space3(t_ms *ms, int i, int n);
int		space_help(t_ms *ms, int x, int n);
int		ft_export3(t_ms *ms, int i, int j);
int		ft_unset(t_ms *ms, char **str, int i);
int		dol_prep(t_ms *ms, int i, int x, int y);
int		ft_export2(t_ms *ms, char **str, int i);
int		heredoc_find(t_ms *ms, char **cmd_args);
int		operator_distribute(t_ms *ms, char *opr);
int		open_files(t_ms *ms, char **file, int fd);
int		ft_export_env(t_ms *ms, char **str, int i);
int		ft_export(t_ms *ms, char **str, int i, int j);
int		check_var3(char *str, int i, int j, t_ms *ms);
int		err(char *error, char *str, t_ms *ms, int type);
int		word_distribute(t_lexer **lexer, t_ms *ms, char *word);
int		child_dup(t_ms	*ms, t_pipex *pipex, char **cmd, int fd);
char	*read_file(void);
char	*in_find(char **cmd);
char	*out_find(char **cmd);
char	**caching(char **str);
char	*get_next_line(int fd);
char	*cmd_builder(t_ms *ms);
char	*dol_check(t_ms *ms, char *ptr);
char	*cmd_build(t_ms *ms, char *word);
char	*ft_concat(char *cmd, char *opt);
char	*ft_join(char *str, char *str2, int i);
char	*dol2(char *ptr, char *str, int i, int n);
void	main_sig(t_ms *ms);
void	ft_free2(t_ms *ms);
void	ft_search(t_ms *ms);
void	goto_start(t_ms *ms);
void	pipe_close(t_pipex *pipex);
void	ctrld(char *line, t_ms *ms);
void	cat_exit(t_ms *ms, char *str);
void	pipe_open(t_pipex *pipex, t_ms *ms);
void	pipex(t_ms *ms, char **argv, int num);
void	my_dup2(int read, int write, t_ms *ms);
void	heredoc(char *str, int file, char *tmp);
void	lstadd_back(t_lexer **lst, t_lexer *new);
void	tree_add_back(t_tree **tree, t_tree *new);
void	tokenizer(t_ms *m, t_lexer **lexer, int i, int j);
t_lexer	*lstnew(void);
t_tree	*tree_new(void);

int g_glob;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

#endif