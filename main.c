/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:14:36 by rchau             #+#    #+#             */
/*   Updated: 2022/01/11 23:03:58 by rchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_exec(t_msh *msh, t_sup *sup)
{
	char	*com;
	int		status;

	status = 0;
	if (ft_if_builtin(msh))
		return (ft_builtin(msh, sup));
	com = ft_command(msh->argv[0], sup->env);
	if (com)
	{
		msh->pid = fork();
		if (msh->pid == 0)
		{
			execve(com, msh->argv, sup->env);
			printf("minishell: %s: No such file or directory\n", com);
			exit(1);
		}
		waitpid(msh->pid, &status, 0);
		g_status = WSTOPSIG(status);
		free(com);
		return (0);
	}
	ft_no_command(msh);
	return (1);
}

t_msh	*ft_execute_command(t_msh *msh, t_sup *sup, int *tmpin_out)
{
	ft_pipe(msh, tmpin_out[0], tmpin_out[1]);
	ft_exec(msh, sup);
	return (msh->next);
}

void	ft_free_msh(t_msh *msh, char *str, int *tmp)
{
	free(str);
	dup2(tmp[0], 0);
	dup2(tmp[1], 1);
	close(tmp[0]);
	close(tmp[1]);
	free(tmp);
	while (msh)
		msh = ft_msh_free_one(msh);
}

int	main(int argc, char **argv, char **env)
{
	char	*str;
	t_msh	*msh;
	int		*tmpin_out;
	t_sup	*sup;
	t_msh	*save_msh;

	sup = (t_sup *)malloc(sizeof(t_sup));
	env_cpy(env, sup, argc, argv);
	while (1)
	{
		tmpin_out = ft_signal_and_tmp_in_out();
		str = readline("minishell$ ");
		if (ft_check_str(str))
			break ;
		msh = ft_mshnew();
		save_msh = msh;
		if (*str != '\0' && msh && !ft_parser(msh, str, sup->env))
			while (msh)
				msh = ft_execute_command(msh, sup, tmpin_out);
		ft_free_msh(save_msh, str, tmpin_out);
	}
	return (0);
}
