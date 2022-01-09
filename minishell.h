/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 21:05:48 by rchau             #+#    #+#             */
/*   Updated: 2022/01/09 19:59:47 by rchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//# include "libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <dirent.h>
# include <signal.h>

int g_status;
int pid;

extern int rl_catch_signals;

typedef struct s_msh
{

	int		argc;
	char	**argv;
	// char	op;   // '|'   NULL
	int		fdin;
	int		fdout;
	int		fdpipe[2];
	int		pid;
	char	*outfile;
	char	*infile;
	int		write_mode; // 2 - O_APPEND; 1 - O_TRUNC
	struct s_msh *next;
	struct s_msh *prev;
}	t_msh;

typedef struct s_sup{
	// t_msh	*msh;
	char 	**env;
}	t_sup;

t_msh bla;
/* ****** PARSER ****** */

void rl_replace_line();

int	ft_argc(char *str, int i);
int	ft_arg_len(char *str, int i);
int	ft_new_command(t_msh **msh_p, char *str, int *k);
int	ft_check_start(char *str, int *j);
int	ft_parser(t_msh *msh, char *str, char **env);

void	ft_free_tmp(char **tmp, int n);
t_msh	*ft_mshnew(void);
int	ft_error(char *str, int i);
int	ft_skip_space(char *str, int i);
char	*ft_get_stop_word(char *str, int *j);

void	ft_double_quotes(char **s, int *j, char **env);
void	ft_check_dollar_in_quotes(char **s, int *i, char **env);
void	ft_quotes(char **s, int *k);
char	*ft_open_quotes(char *str, char **env);
int	ft_check_open_quotes(char *str);

int	ft_redirect(t_msh *msh, char *str, int *j);
int	ft_redirect_input(char *str, int *j, t_msh *msh);
int	ft_redirect_output(char *str, int *j, t_msh *msh);
int	ft_stop_word(char *str, int *i, t_msh *msh);
char	*ft_get_file_name(char *str, int *i);

char	*ft_get_env(char **env, char *key);
void	ft_dollar(char **s, int *j, char **env);
void	ft_exit_status(char **s, int *j);

int		ft_cd(char **arg, char **env);
int		ft_echo(char **arg, char **env);
void	status_writing();
int		ft_exit(char **arg, char **env);
int		error_nar(char *comm, char *arg);
int 	error_tma(char *arg);
int		ft_export(char **arg, t_sup *sup);
int		check_argv_ex(char *argv);
void	print_quotes(char **env);
int		env_sort(char **env);
int		ft_unset(char **argv, char **env);
int		unset_checker(char *argv);
void	uns_rewrite(char **env, int n);
int		error_nsfod(char *comm, char *arg);
int		error_nva(char *comm, char *arg);
int		error_malloc();
void	free_mass(char **mass);
void	one_mas_fr_two(t_sup *sup, char *from);
int		env_search_same(char *arg, char **env);
int		ft_env(char **argv, char **env);
int		ft_pwd();
void	cd_chdirs(char *sup, char **env);
void	cd_currpwd(char **env);
void	cd_prevpwd(char **env);
void	cd_oldpwd(char **env);
void	cd_home(char **env);

///***libft**/
//
// char	*ft_strjoin(char const *s1, char const *s2);
// char	*ft_strdup(const char *s1);
// char	*ft_substr(char const *s, unsigned int start, size_t	len);
// int		ft_isalnum(int c);
// size_t	ft_strlen(const char *s);
// int		ft_strncmp(const char *s1, const char *s2, size_t	n);
// char	*ft_itoa(int n);
// char	*vnos(char *rev, int n, int i);
// int		size(int num);
// void	*ft_memmove(void *dst, const void *src, size_t	len);
// char	**ft_split(char const *s, char c);
// int		couword(char const *str, char cut);
// void	line(char **stolb, int nw, const char *s, char cut);
// void	makeclean(char **s, int i);
// int		ft_memcmp(const void *s1, const void *s2, size_t	n);
// void	*ft_memcpy(void *dst, const void *src, size_t	n);
// char	*ft_strchr(const char *s, int c);
// size_t	ft_strlcpy(char *dst, const char *src, size_t	dstsize);
// int		ft_isalpha(int c);
// char	*ft_strnstr(const char *haystack, const char *needle, size_t	len);
// int		ft_isdigit(int c);
// char	*ft_strrchr(const char *s, int c);
// void	*ft_memset(void *b, int c, size_t	len);
// void	*ft_calloc(size_t	count, size_t	size);
// int		ft_atoi(const char *str);

#endif


// -lreadline  -L/Users/rchau/.brew/Cellar/readline/8.1.1/lib/ -I/Users/rchau/.brew/Cellar/readline/8.1.1/include