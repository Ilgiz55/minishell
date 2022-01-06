#include "minishell.h"

void error_tma(char *arg)
{
	write(1, arg, ft_strlen(arg));
	write(1, ": too many arguments\n", 21);
}

int error_nar(char *comm, char *arg)
{
	write(1, comm, ft_strlen(comm));
	write(1, ": ", 2);
	write(1, arg, ft_strlen(arg));
	write(1, ": numeric argument required\n", 28);
	return (1);
}

int ft_exit(char **arg, char **env)
{
	int	i;
	int j;
	char *sup;

	i = -1;
	if (!arg[1])
		exit (0);
	if (arg[2])
		error_tma(arg[0]);
	while (arg[1][++i])
		if (!ft_isalnum(arg[1][i]) || i > 19)
			if(error_nar(arg[0], arg[1]))
				return (1);
	return (0);
}