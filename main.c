/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:14:36 by rchau             #+#    #+#             */
/*   Updated: 2022/01/10 15:28:23 by rchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_cpy(char **from, t_sup *sup, int argc, char **argv)
{
	int	i;

	(void)argc;
	(void)argv;
	g_status = 0;
	i = 0;
	while (from[i])
		i++;
	sup->env = (char **)malloc(sizeof(char *) * (i + 1));
	sup->env[i] = NULL;
	while (--i >= 0)
	{
		sup->env[i] = ft_strdup(from[i]);
		if (!sup->env[i])
		{
			g_status = error_malloc();
			exit (g_status);
		}
	}
	i = env_search_same("SHLVL", sup->env);
	if (i >= 0)
		sup->env[i][6] = sup->env[i][6] + 1;
}

void	ft_pipe(t_msh *msh, int tmpin, int tmpout)
{
	if (msh->infile)
		msh->fdin = open(msh->infile, O_RDONLY, 0644);
	else if (msh->prev && !msh->prev->outfile)
		msh->fdin = msh->prev->fdpipe[0];
	else
		msh->fdin = dup(tmpin);
	if (msh->outfile && msh->write_mode == 2)
		msh->fdout = open(msh->outfile, O_WRONLY | O_APPEND);
	else if (msh->outfile && msh->write_mode == 1)
		msh->fdout = open(msh->outfile, O_WRONLY | O_TRUNC);
	else if (msh->next)
	{
		pipe(msh->fdpipe);
		msh->fdout = msh->fdpipe[1];
	}
	else
		msh->fdout = dup(tmpout);
	dup2(msh->fdin, 0);
	close(msh->fdin);
	dup2(msh->fdout, 1);
	close(msh->fdout);
}

void	ft_free_msh(t_msh *msh, char *str, int *tmp)
{
	t_msh	*tmp_msh;
	int		i;

	free(str);
	dup2(tmp[0], 0);
	dup2(tmp[1], 1);
	close(tmp[0]);
	close(tmp[1]);
	while (msh)
	{
		if (msh->argv)
		{
			i = -1;
			while (msh->argv[++i])
				free(msh->argv[i]);
			free(msh->argv);
		}
		if (msh->outfile)
			free(msh->outfile);
		if (msh->infile)
			free(msh->infile);
		tmp_msh = msh;
		msh = msh->next;
		free(tmp_msh);
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*str;
	t_msh	*msh;
	int		*tmpin_out;
	t_sup	*sup;

	sup = (t_sup *)malloc(sizeof(t_sup));
	env_cpy(env, sup, argc, argv);
	while (1)
	{
		tmpin_out = ft_signal_and_tmp_in_out();
		str = readline("minishell$ ");
		if (ft_check_str(str))
			break ;
		msh = ft_mshnew();
		if (msh && !ft_parser(msh, str, sup->env))
		{
			while (msh)
			{
				ft_pipe(msh, tmpin_out[0], tmpin_out[1]);
				ft_exec(msh, sup);
				msh = msh->next;
			}
		}
		ft_free_msh(msh, str, tmpin_out);
	}
	return (0);
}
