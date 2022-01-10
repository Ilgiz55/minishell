/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:05:28 by rchau             #+#    #+#             */
/*   Updated: 2022/01/10 21:25:30 by rchau            ###   ########.fr       */
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
	// printf("%d", g_status.child);
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
	struct sigaction s_sa;

	sigemptyset(&s_sa.sa_mask);
	sigaddset(&s_sa.sa_mask, SIGINT);
	sigaddset(&s_sa.sa_mask, SIGQUIT);
	s_sa.sa_handler = ft_handler;
	sigaction(SIGINT, &s_sa, 0);
	sigaction(SIGQUIT, &s_sa, 0);

	// signal(SIGINT, ft_handler);
	// signal(SIGQUIT, ft_handler);
	tmpin_out = (int *)malloc(sizeof(int) * 2);
	tmpin_out[0] = dup(0);
	tmpin_out[1] = dup(1);
	return (tmpin_out);
}
