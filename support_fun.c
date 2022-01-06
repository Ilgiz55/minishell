#include "minishell.h"

int	error_nsfod(char *comm, char *arg)
{
	write(1, comm, ft_strlen(comm));
	write(1, ": ", 2);
	write(1, arg, ft_strlen(arg));
	write(1, ": No such file or directory\n", 28);
	exit_status = 1;
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

int error_malloc()
{
	write(1, "Malloc error\n", 13);
	return (1);
}

void	free_mass(char **mass)
{
	int i;

	i = 0;
	while (mass[i])
		i++;
	while (--i >= 0)
	{
		free(mass[i]);
		mass[i] = NULL;
	}
	free(mass);
	mass = NULL;
}

void	one_mas_fr_two(t_sup *sup, char *from)
{
	int 	i;
	char	**mass;

	i = 0;
	while(sup->env[i])
	{
		i++;
	}
	mass = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while ((sup->env)[i])
	{
		mass[i] = ft_strdup((sup->env)[i]);
		i++;
	}
	mass[i] = malloc(sizeof(char) * (ft_strlen(from)));
	ft_memcpy(mass[i], from, ft_strlen(from));
	free_mass(sup->env);
	mass[i + 1] = NULL;
	sup->env = mass;
}

int	env_search_same(char *arg, char **env)
{
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	while (arg[k] != '=' && arg[k])
		k++;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=' && env[i][j])
		{
			j++;
		}
		if (!ft_memcmp(arg, env[i], j) && k == j)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}
