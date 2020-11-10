/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:02:45 by hthomas           #+#    #+#             */
/*   Updated: 2020/04/14 20:08:45 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

char				*fill_positivenbr_base(long nbr, char *base,
					char *res, int i);
char				*fill_nbr_base(char *res, long nbr, char *base, int sign);
char				*ft_strrev_minus_1(char *res);
void				ft_swap(void *a, void *b);
int					ft_atoi(const char *str);
int					ft_atoi_strict(const char *nptr);
long				ft_atol(const char *nptr);
float				ft_atof(const char *str);
double				ft_pow(double nb, double pow);
int					check_base(char *base);
int					ft_atoi_base(char *str, char *base);
char				*ft_convert_base(char *nbr, char *base_from, char *base_to);
int					ft_nbrlen(int n);
char				*ft_itoa(int nbr);
char				*ft_uitoa(unsigned int n);
char				*ft_ltoa(long n);
char				*ft_ltoa_base(unsigned long nb, char *base_to);
char				*ft_uitoa_base(unsigned int nb, char *base_to);
int					ft_islower(int c);
int					ft_isupper(int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_issign(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				ft_putchar(int c);
void				ft_putchar_fd(char c, int fd);
void				ft_putnbr(int nb);
void				ft_putnbr_fd(int nb, int fd);
void				ft_putnbr_unsigned_fd(unsigned int nb, int fd);
void				ft_putnbr_unsigned(unsigned int nb);
void				ft_putstrn(const char *str, unsigned int n);
void				ft_putstrn_fd(const char *str, int fd, unsigned int n);
void				ft_putstr_fd(const char *str, int fd);
void				ft_putstr(const char *str);
void				ft_putendl_fd(char const *s, int fd);
void				ft_puthex(unsigned int hex, int upper);
void				ft_putpointer(unsigned long long pointer);
int					ft_count_len_hex(unsigned long long hex);
char				*ft_chardup(char const c);
size_t				ft_strlen(const char *str);
char				*ft_strdup(const char *src);
char				*ft_strcpy(char *dest, const char *src);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
char				*ft_strcat(char *dest, const char *src);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp_rev(const char *s1, const char *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strstr(const char *str, const char *to_find);
char				*ft_strnstr(const char *str, const char *to_find,
					size_t len);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_in_charset(char c, char const *charset);
int					ft_is_from_charset(const char *str, const char *charset);
char				**ft_split(char const *s, char c1);
char				**ft_split_set(const char *str, char *charset);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoin_sep(int size, char **strs, char *sep);
char				*ft_strtrim(char const *str, char const *set);
void				*ft_calloc(size_t count, size_t size);
void				ft_bzero(void *b, size_t n);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **alst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
char				*ft_itoa_width(int nb, int width);
int					ft_nbrlen(int n);
int					ft_max_int(int a, int b);
float				ft_max_float(float a, float b);
int					ft_min_int(int a, int b);
float				ft_min_float(float a, float b);

#endif
