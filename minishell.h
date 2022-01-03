/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 21:05:48 by rchau             #+#    #+#             */
/*   Updated: 2022/01/03 17:38:28 by rchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

typedef struct s_msh
{

	int		argc;
	char	**argv;
	char	op;   // '|'   NULL
	int		fdin;
	int		fdout;
	struct s_msh *next;
}	t_msh;


/* ****** PARSER ****** */

int	ft_argc(char *str, int i);
int	ft_arg_len(char *str, int i);
int	ft_new_command(t_msh **msh_p, char *str, int *k);
int	ft_check_start(char *str, int *j);
int	ft_parser(t_msh *msh, char *str, char **env);

void	ft_free_tmp(char **tmp, int n);
t_msh	*ft_mshnew(void);
int	ft_error(char *str);
int	ft_skip_space(char *str, int i);
char	*ft_get_stop_word(char *str, int *j);

void	ft_double_quotes(char **s, int *j, char **env);
void	ft_check_dollar_in_quotes(char **s, int *i, char **env);
void	ft_quotes(char **s, int *k);
char	*ft_open_quotes(char *str, char **env);
int	ft_check_open_quotes(char *str);

int	ft_redirect(t_msh *msh, char *str, int *j);
int	ft_redirect_input(char *str, int *j, t_msh *msh);
int	ft_redirect_output(char *str, int *j, t_msh *msh, int flag);
int	ft_stop_word(char *str, int *i, t_msh *msh);
char	*ft_get_file_name(char *str, int *i);

char	*ft_get_env(char **env, char *key);
void	ft_dollar(char **s, int *j, char **env);

#endif


