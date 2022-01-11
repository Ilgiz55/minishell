/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 19:03:04 by laubrey           #+#    #+#             */
/*   Updated: 2022/01/11 17:54:01 by rchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_nsfod(char *comm, char *arg)
{
	write(1, comm, ft_strlen(comm));
	write(1, ": ", 2);
	write(1, arg, ft_strlen(arg));
	write(1, ": No such file or directory\n", 28);
	g_status = 1;
	return (1);
}

int	error_nva(char *comm, char *arg)
{
	write(1, comm, ft_strlen(comm));
	write(1, ": \'", 3);
	write(1, arg, ft_strlen(arg));
	write(1, "\': not a valid identifier\n", 26);
	return (1);
}

int	error_malloc(void)
{
	write(1, "Malloc error\n", 13);
	return (1);
}

int	error_tma(char *arg)
{
	write(1, arg, ft_strlen(arg));
	write(1, ": too many arguments\n", 21);
	return (1);
}

int	error_nar(char *comm, char *arg)
{
	write(1, comm, ft_strlen(comm));
	write(1, ": ", 2);
	write(1, arg, ft_strlen(arg));
	write(1, ": numeric argument required\n", 28);
	return (1);
}
