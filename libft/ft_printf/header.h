/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <ahonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:35:49 by ahonchar          #+#    #+#             */
/*   Updated: 2018/05/08 12:20:40 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# define TYPES	"sSpdDioOuUxXcC%"
# define FLAGS	"#0-+ "
# define MODS	"hljz"
# include <stdlib.h>
# include <stdarg.h>
# include <locale.h>

typedef struct		s_print
{
	_Bool			align;
	_Bool			sign;
	_Bool			space;
	_Bool			specformat;
	_Bool			zero;
	int				width;
	int				precision;
	_Bool			set_precision;
	char			typemod;
	_Bool			doublemod;
	char			add;
	char			type;
	char			*out;
	struct s_print	*next;
}					t_print;

int					ft_atoi(const char *str);
int					ft_isdigit(int c);
void				ft_strclr(char *s);
void				*ft_memset(void *dest, int c, size_t n);
char				*ft_strchr(const char *s, int c);
char				*ft_strcpy(char *dst, const char *src);
size_t				ft_strlen(const char *s);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strnew(size_t size);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_itoa_long(void *num, char type);
char				*ft_strrev(char *s);
int					my_ret(t_print *list, int ret);
void				parse_percent(char **str, t_print *list);
int					parse_unicode(char *str, unsigned value);
int					contains(char *str, char c);
void				delete_minus(char **src);
t_print				*parse_format(char *format);
int					valid(char *format);
int					processing_string(t_print *list, va_list arg);
int					processing_percent(t_print *list, va_list arg);
int					processing_number(t_print *list, va_list arg);
int					processing_char(t_print *list, va_list arg);
char				*proc_width(t_print *list, char *src, int len, char c);
char				*ft_itoa_base(unsigned long value, int base, _Bool upper);
char				*process_int_precision(t_print *list,
						char *out, char *prefix);
int					processing_hex(t_print *list, va_list arg);
int					processing_oct(t_print *list, va_list arg);
int					processing_ptr(t_print *list, va_list arg);
void				star(t_print *list, va_list arg);

#endif
