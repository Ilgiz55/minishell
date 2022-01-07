#include "minishell.h"

int unset_checker(char *argv)
{
	int	i;
	int j;

	g_status = 0;
	i = 0;
	if (argv[0] != '_' && !ft_isalpha(argv[0]))
	{
		g_status = error_nva("unset", argv);
		return (g_status);
	}
	while (argv[i])
	{
		if (argv[i] != '_' && argv[i] != '=' && argv[i] != '+'
		&& !ft_isalpha(argv[i]) && !ft_isdigit(argv[i]))
			g_status = error_nva("unset", argv);
		if (argv[i] == '+' && argv[i + 1] != '=')
			g_status = error_nva("unset", argv);
		i++;
	}
	return (g_status);
}

int uns_rewrite(char **env, int n)
{
	char *sup;

	while (env[n])
	{
		sup = env[n + 1];
		free(env[n]);
		if (sup != NULL)
		{
			env[n] = ft_strdup(sup);
			n++;
		}
		else
		{
			env[n] = NULL;
			return (0);
		}
	}
	return (0);
}

int ft_unset(char **argv, char **env)
{
	int	i;
	int j;

	i = 0;
	if (!argv[1])//Возвращает 0 без аргументов
		return (0);
	while(argv[++i])
	{
		if (!unset_checker(argv[i]))
		{
			j = env_search_same(argv[i], env);
			if (j >= 0)
				uns_rewrite(env, j);
			g_status = 0;
		}
		i++;
	}
	return (g_status);
}

//while (str[i])
//{
//	if (str[i] != '_' && str[i] != '=' && str[i] != '+'
//	&& !ft_isalpha(str[i]) && !ft_isdigit(str[i]))
//		return (1);
//	if (str[i] == '+' && str[i + 1] != '=')
//		return (1);
//	if (str[i] == '=' && !fl)
//		return (1);
//	else if ((str[i] == '=' || str[i] == '+') && fl)
//		break ;
//	i++;
//}