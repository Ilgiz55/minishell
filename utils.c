/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:05:28 by rchau             #+#    #+#             */
/*   Updated: 2022/01/10 22:37:25 by rchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handler(int sig_num)
{
	if (sig_num == SIGINT && !g_status.child)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig_num == SIGINT && g_status.child)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig_num == SIGQUIT && !g_status.child)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig_num == SIGQUIT && g_status.child)
	{
		write(1, "Quit: 3\n", 8);
		rl_on_new_line();
	}
}

int	ft_check_str(char *str)
{
	if (!str)
	{
		printf("exit\n");
		return (1);
	}
	if (*str != '\0')
		add_history(str);
	return (0);
}

int	*ft_signal_and_tmp_in_out(void)
{
	int					*tmpin_out;
	struct sigaction	s_sa;

	sigemptyset(&s_sa.sa_mask);
	sigaddset(&s_sa.sa_mask, SIGINT);
	sigaddset(&s_sa.sa_mask, SIGQUIT);
	s_sa.sa_handler = ft_handler;
	sigaction(SIGINT, &s_sa, 0);
	sigaction(SIGQUIT, &s_sa, 0);
	tmpin_out = (int *)malloc(sizeof(int) * 2);
	tmpin_out[0] = dup(0);
	tmpin_out[1] = dup(1);
	return (tmpin_out);
}

void	env_cpy(char **from, t_sup *sup, int argc, char **argv)
{
	int	i;

	(void)argc;
	(void)argv;
	g_status.exit = 0;
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
			g_status.exit = error_malloc();
			exit (g_status.exit);
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
