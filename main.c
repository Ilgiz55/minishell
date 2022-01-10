/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:14:36 by rchau             #+#    #+#             */
/*   Updated: 2022/01/10 22:47:19 by rchau            ###   ########.fr       */
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

t_msh	*ft_execute_command(t_msh *msh, t_sup *sup, int *tmpin_out)
{
	ft_pipe(msh, tmpin_out[0], tmpin_out[1]);
	ft_exec(msh, sup);
	return (msh->next);
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
	g_status.child = 0;
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
