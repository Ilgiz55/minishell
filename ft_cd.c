#include "minishell.h"

void	cd_chdirs(char *sup, char **env)
{
	int i;
	int j;
	char *oldpwd;

	oldpwd = malloc(sizeof(1024,1));
	getcwd(oldpwd, 1024);
	if (chdir(sup))
		exit_status = error_nsfod("cd",sup);
	else
	{
		i = env_search_same("OLDPWD\0", env);
		if (i >= 0)
		{
			free(env[i]);
			env[i] = ft_strjoin("OLDPWD=\0", oldpwd);
		}
		j = env_search_same("PWD\0", env);
		if (j >=0)
		{
			free(env[j]);
			env[j] = ft_strjoin("PWD=\0", sup);
		}
		exit_status = 0;
	}
	free(oldpwd);
	
}

void	cd_currpwd(char **env)
{
	char *sup;

	sup = malloc(sizeof(1024, 1));
	if (getcwd(sup, 1024))
		cd_chdirs(sup, env);
	else
	{
		write(2, "PATH did not found\n", 19);
		exit_status = 1;
	}
	free(sup);
}

void	cd_prevpwd(char **env)
{
	char *sup;
	char *temp;

	sup = malloc(sizeof(1024, 1));
	if (getcwd(sup, 1024))
	{
		temp = ft_strrchr(sup, '/');
		while (*temp)
		{
			temp = NULL;
			temp++;
		}
		cd_chdirs(sup, env);
	}
	else
	{
		write(2, "PATH did not found\n", 19);
		exit_status = 1;
	}
	free(sup);
}

void	cd_oldpwd(char **env)
{
	char *sup;
	int i;

	i = env_search_same("OLDPWD\0", env);
	if (i >= 0 && env[i][5] != '\0')
	{
		sup = ft_substr(env[i], 7, ft_strlen(&env[i][7]));
		cd_chdirs(sup, env);
	}
	else if (i >= 0 && env[i][5] == '\0')//HOME="" не ошибка, возвращает 0, не делает ничего
	{
		write(1, "\n", 1);
		cd_currpwd(env);
	}
	else
	{
		exit_status = 1;
		write(1, "cd: OLDPWD not set\n", 19);
	}
}


void	cd_home(char **env)
{
	char *sup;
	int i;

	i = env_search_same("HOME", env);
	if (i >= 0 && env[i][5] != '\0')
	{
		sup = ft_substr(env[i], 5, ft_strlen(&env[i][5]));
		cd_chdirs(sup, env);
	}
	else if (i >= 0 && env[i][5] == '\0')//HOME="" не ошибка, возвращает 0, не делает ничего
		cd_currpwd(env);
	else
	{
		exit_status = 1;
		write(1, "cd: HOME not set\n", 17);
	}
}



int ft_cd(char **arg, char **env)
{
	if (!ft_strncmp(arg[1], "..\0", 3))
		cd_prevpwd(env);
	else if (!ft_strncmp(arg[1], ".\0", 2))
		cd_currpwd(env);
	else if (!ft_strncmp(arg[1], "-\0", 2))
		cd_oldpwd(env);
	else if (!arg[1])
		cd_home(env);
	else
		cd_chdirs(arg[1], env);
	return (0);
}
