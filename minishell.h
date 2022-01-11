/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 21:05:48 by rchau             #+#    #+#             */
/*   Updated: 2022/01/10 22:40:22 by rchau            ###   ########.fr       */
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
# include <sys/types.h>
# include <dirent.h>
# include <signal.h>

typedef struct s_status
{
	int	exit;
	int	child;
}	t_status;

t_status	g_status;

typedef struct s_msh
{
	int				argc;
	char			**argv;
	int				fdin;
	int				fdout;
	int				fdpipe[2];
	int				pid;
	char			*outfile;
	char			*infile;
	int				write_mode;
	struct s_msh	*next;
	struct s_msh	*prev;
}	t_msh;

typedef struct s_sup
{
	char	**env;
}	t_sup;

int		ft_builtin(t_msh *msh, t_sup *sup);
int		ft_if_builtin(t_msh *msh);

int		ft_new_command(t_msh **msh_p, char *str, int *k);
int		ft_check_start(char *str, int *j);
int		ft_start_parser(t_msh *msh, char *str, int *i);
int		ft_parser(t_msh *msh, char *str, char **env);

void	ft_free_tmp(char **tmp, int n);
t_msh	*ft_mshnew(void);
int		ft_error(char *str, int i);
int		ft_skip_space(char *str, int i);
char	*ft_get_stop_word(char *str, int *j);

int		ft_argc(char *str, int i);
int		ft_arg_len(char *str, int i);

void	ft_double_quotes(char **s, int *j, char **env);
void	ft_check_dollar_in_quotes(char **s, int *i, char **env);
void	ft_quotes(char **s, int *k);
char	*ft_open_quotes(char *str, char **env);
int		ft_check_open_quotes(char *str);

int		ft_redirect(t_msh *msh, char *str, int *j);
int		ft_redirect_input(char *str, int *j, t_msh *msh);
int		ft_redirect_output(char *str, int *j, t_msh *msh);
int		ft_stop_word(char *str, int *i, t_msh *msh);
char	*ft_get_file_name(char *str, int *i);

char	*ft_get_env(char **env, char *key);
void	ft_dollar(char **s, int *j, char **env);
void	ft_exit_status(char **s, int *j);

int		ft_exec(t_msh *msh, t_sup *sup);
char	*ft_command_dir(char *str, char **env);
int		has_command(char *path, char *str);
char	*ft_command(char *str, char **env);
void	ft_free_path(char **path_list);

void	ft_handler(int sig_num);
int		ft_check_str(char *str);
int		*ft_signal_and_tmp_in_out(void);
t_msh	*ft_execute_command(t_msh *msh, t_sup *sup, int *tmpin_out);
void	env_cpy(char **from, t_sup *sup, int argc, char **argv);
void	ft_pipe(t_msh *msh, int tmpin, int tmpout);
void	ft_free_msh(t_msh *msh, char *str, int *tmp);

int		ft_cd(char **arg, char **env);
int		ft_echo(char **arg);
void	status_writing(void);
int		ft_exit(char **arg, char **env);
int		error_nar(char *comm, char *arg);
int		error_tma(char *arg);
int		ft_export(char **arg, t_sup *sup);
int		check_argv_ex(char *argv);
void	print_quotes(char **env);
int		env_sort(char **env);
int		ft_unset(char **argv, char **env);
int		unset_checker(char *argv);
void	uns_rewrite(char **env, int n);
int		error_nsfod(char *comm, char *arg);
int		error_nva(char *comm, char *arg);
int		error_malloc(void);
void	free_mass(char **mass);
void	one_mas_fr_two(t_sup *sup, char *from);
int		env_search_same(char *arg, char **env);
int		ft_env(char **argv, char **env);
int		ft_pwd(void);
void	cd_chdirs(char *sup, char **env);
void	cd_currpwd(char **env);
void	cd_prevpwd(char **env);
void	cd_oldpwd(char **env);
void	cd_home(char **env);

#endif
