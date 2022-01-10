/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:05:28 by rchau             #+#    #+#             */
/*   Updated: 2022/01/10 15:06:56 by rchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	tmpin_out = (int *)malloc(sizeof(int) * 2);
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
	tmpin_out[0] = dup(0);
	tmpin_out[1] = dup(1);
	return (tmpin_out);
}
