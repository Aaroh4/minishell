/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:22:20 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/27 12:29:33 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# include <unistd.h>
# include <stddef.h>
# include <stdarg.h>
# include <stdlib.h>

// LIBFT

int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_isalnum(int i);
int		ft_isalpha(int i);
int		ft_isascii(int i);
int		ft_isdigit(int i);
int		ft_isprint(int i);
int		ft_isspace(int i);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *s1, const void *s2, size_t n);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strchr(const char *s, int i);
char	*ft_strdup(const char *s);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strcpos(const char *s, char c);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
int		ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
int		ft_tolower(int i);
int		ft_toupper(int i);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char *str, char *charset);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

// GNL

char	*create_list(int fd, char *str);
char	*get_next_line(int fd);
int		ft_str_chr(char *str);
char	*ft_strrjoin(char const *s1, char const *s2);
char	*ft_strrdup(const char *src);
char	*ft_subbstr(char const *s, unsigned int start, size_t len);
int		ft_strrlen(const char *str);
char	*ft_read(int fd, char *str, char *buf);
char	*ft_sub(char *str);
void	freestr(char **str);

// PRINTF

int		ft_printf(const char *str, ...);
int		printing(va_list arg, char c);
int		ft_putchar(char c);
int		ft_putstr(char *str);
int		count(int n);
int		ft_printhex(long n, int base, char c);
int		ft_printptr(unsigned long n);

// TIME AND SPACE

char	**ft_split_time_space(char const *s, char c);
int		ft_check(int i, const char *str);
int		freemem(char **arr, int size);
int		ft_checker(char const *s, int i, int check);
int		ft_incrj(int i, char const *s, int check, char c);


#endif
