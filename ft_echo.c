#include "minishell.h"

void	status_writing()
{
	char *st;

	st = ft_itoa(exit_status);
	write(1, st, ft_strlen(st));
	free(st);
}

int	ft_echo(char **argv, char **env)
{
	int i;
	int j;

	i = 0;
	if (argv[1] && !ft_strncmp(argv[1], "-n\0", 3))
		i++;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!ft_strncmp(&argv[i][j], "$?", 2))
			{
				status_writing();
				j++;
			}
			else
				write(1, &argv[i][j], 1);
		}
		if (argv[i + 1])
			write(1, " ", 1);
	}
	if (!argv[1] || ft_strncmp(argv[1], "-n\0", 3))
		write(1, "\n", 1);
	exit_status = 0;
	return (0);
}