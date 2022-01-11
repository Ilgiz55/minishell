/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:05:28 by rchau             #+#    #+#             */
/*   Updated: 2022/01/11 23:04:40 by rchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_msh	*ft_msh_free_one(t_msh *msh)
{
	int	i;

	if (msh->argv)
	{
		i = 0;
		while (msh->argv[i])
			free(msh->argv[i++]);
		free(msh->argv);
	}
	if (msh->outfile)
		free(msh->outfile);
	if (msh->infile)
		free(msh->infile);
	if (msh->next)
	{
		msh = msh->next;
		free(msh->prev);
		msh->prev = NULL;
	}
	else
	{
		free(msh);
		msh = NULL;
	}
	return (msh);
}

void	ft_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
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
	int	*tmpin_out;

	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
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
