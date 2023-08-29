/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:59:22 by rugrigor          #+#    #+#             */
/*   Updated: 2023/08/29 13:17:29 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *str);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(char *str, int n);
char	*ft_strrchr(const char *str, int n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcpm(char *s1, char *s2);
void	*ft_memset(void *str, int c, size_t n);
void	*ft_memcpy(void *str, const void *dest, size_t n);
void	*ft_memmove(void *str, const void *dest, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memchr(const void *str, int c, size_t n);
int		ft_memcmp(const void *str1, const void *str2, size_t n);
size_t	ft_strlcpy(char *dest, const char *str, size_t destn);
char	*ft_strdup(const char *str);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t p, size_t n);
char	*ft_strnstr(const char *big, const char *lit, size_t len);
size_t	ft_strlcat(char *dest, const char *str, size_t destn);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_itoa(int n);
int		ft_strcmp(char *s1, char *s2);
int		ft_strrcmp(char *str, char *cmp);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));

#endif
