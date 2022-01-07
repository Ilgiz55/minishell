#include "minishell.h"

int	env_sort(char **env)
{
	int		i;
	int 	j;
	int 	k;
	char	**env_sup;
	char	*check;

	i = 0;
	while (env[i])
		i++;
	env_sup = (char **)malloc(sizeof(char *) * (i + 1));
	env_sup[i] = NULL;
	while (--i >= 0)
	{
		check = ft_strdup(env[i]);
		k = -1;
		j = 0;
		while (env[++k])
			if (ft_strncmp(check, env[k], ft_strlen(env[i]) + 1) > 0)
				j++;
		env_sup[j] = check;
	}
	i = -1;
	while (env_sup[++i])
	{
		write(1, "declare -x ", 11);
		print_quotes(env_sup[i]);
	}
	free_mass(env_sup);
	return (0);
}

void	print_quotes(char *str)
{
	while (str && *str != '=' && *str != '\0')
	{
		write(1, str, 1);
		str++;
	}
	if (str && *str == '=')
	{
		write(1, "=\"", 2);
		str++;
		while (str && str != NULL && *str != 0)
		{
			write(1, str, 1);
			str++;
		}
		write(1, "\"", 1);
	}
	write(1, "\n", 1);
}

int check_argv_ex(char *argv)
{
	if (!(ft_isalpha(argv[0])) || argv[0] == '=')
		return (1);
	while (*argv && *argv != '=')
	{
		if (*argv == '.')
			return (1);
		argv++;
	}
	return (0);
}

int	ft_export(char **argv, t_sup *sup)
{
	int i;
	int j;

	i = 0;
	if (!argv[1])
	{
		g_status = env_sort(sup->env);
		return (g_status);
	}
	while (argv[++i])
	{
		if (check_argv_ex(argv[i]))
		{
			g_status = error_nva(argv[0], argv[i]);
		}
		else
		{
			j = env_search_same(argv[i], sup->env);
			if (j >= 0)
			{
				free(sup->env[j]);
				sup->env[j] = ft_strdup(argv[i]);
			}
			else
			{
				one_mas_fr_two(sup, argv[i]);
			}
			g_status = 0;
		}
	}
	return (g_status);
}
