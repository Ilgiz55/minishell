#include "minishell.h"

void	env_cpy(char **from, t_sup *sup)
{
	int	i;

	i = 0;
	while (from[i])
		i++;
	sup->env = (char **)malloc(sizeof(char *) * (i + 1));
	sup->env[i] = NULL;
	while (--i >= 0)
	{
		sup->env[i] = ft_strdup(from[i]);
		if (!sup->env[i])
		{
			g_status = error_malloc();
			exit (g_status);
		}
	}
	i = env_search_same("SHLVL", sup->env);
	if (i >= 0)
		sup->env[i][6] = sup->env[i][6] + 1;
}

int	ft_builtin(t_msh *msh, t_sup *sup)
{
	if (!ft_strncmp(msh->argv[0], "echo\0", 5))
		g_status = (ft_echo(msh->argv, sup->env));
	else if (!ft_strncmp(msh->argv[0], "pwd\0", 4))
		g_status = (ft_pwd());
	else if (!ft_strncmp(msh->argv[0], "env\0", 4))
		g_status = (ft_env(msh->argv, sup->env));
	else if (!ft_strncmp(msh->argv[0], "export\0", 7))
		g_status = (ft_export(msh->argv, sup));
	else if (!ft_strncmp(msh->argv[0], "unset\0", 6))
		g_status = (ft_unset(msh->argv, sup->env));
	else if (!ft_strncmp(msh->argv[0], "cd\0", 3))
		g_status = (ft_cd(msh->argv, sup->env));
	else if (!ft_strncmp(msh->argv[0], "exit\0", 5))
		g_status = (ft_exit(msh->argv, sup->env));
	return (1);
}

int	ft_if_builtin(t_msh *msh)
{
	int		i;
	char	**b_com;

	b_com = (char **)malloc(sizeof(char *) * 7);
	b_com[0] = "echo";
	b_com[1] = "cd";
	b_com[2] = "pwd";
	b_com[3] = "export";
	b_com[4] = "unset";
	b_com[5] = "env";
	b_com[6] = "exit";
	i = 0;
	while (i < 7)
	{
		if (!ft_strncmp(msh->argv[0], b_com[i], \
			ft_strlen(msh->argv[0]) | ft_strlen(b_com[i])))
		{
			free(b_com);
			return (1);
		}
		i++;
	}
	free(b_com);
	return (0);
}

int	has_command(char *path, char *str)
{
	DIR				*dirp;
	struct dirent	*rdir;

	dirp = opendir(path);
	rdir = readdir(dirp);
	while (rdir)
	{
		if (!ft_strncmp(rdir->d_name, str, \
			ft_strlen(rdir->d_name) | ft_strlen(str)))
		{
			closedir(dirp);
			return (1);
		}
		rdir = readdir(dirp);
	}
	closedir(dirp);
	return (0);
}

void	ft_free_path(char **path_list)
{
	int	i;

	i = -1;
	while (path_list[++i])
		free(path_list[i]);
	free(path_list);
}

char *ft_command_dir(char *str, char **env)
{
	char	**path_list;
	char	*path_line;
	char	*path;
	int		i;

	path_line = ft_get_env(env, "PATH");
	path_list = ft_split(path_line, ':');
	free(path_line);
	i = -1;
	while (path_list[++i])
	{
		if (has_command(path_list[i], str))
		{
			path = ft_strdup(path_list[i]);
			ft_free_path(path_list);
			return (path);
		}
	}
	ft_free_path(path_list);
	return (NULL);
}

char	*ft_command(char *str, char **env)
{
	char	*dir;
	char	*com;
	char	*tmp;
	int		i;

	if ((str[0] == '.' && str[1] == '/') || str[0] == '/')
		return (ft_strdup(str));
	dir = ft_command_dir(str, env);
	if (!dir)
		return (NULL);
	tmp = ft_strjoin(dir, "/");
	free (dir);
	com = ft_strjoin(tmp, str);
	free(tmp);
	return (com);
}

void	ft_pipe(t_msh *msh, int tmpin, int tmpout)
{
	if (msh->infile)
		msh->fdin = open(msh->infile, O_RDONLY, 0644);
	else if (msh->prev && !msh->prev->outfile)
		msh->fdin = msh->prev->fdpipe[0];
	else
		msh->fdin = dup(tmpin);
	if (msh->outfile && msh->write_mode == 2)
		msh->fdout = open(msh->outfile, O_WRONLY | O_APPEND);
	else if (msh->outfile && msh->write_mode == 1)
		msh->fdout = open(msh->outfile, O_WRONLY | O_TRUNC);
	else if (msh->next)
	{
		pipe(msh->fdpipe);
		msh->fdout = msh->fdpipe[1];
	}
	else
		msh->fdout = dup(tmpout);
	dup2(msh->fdin, 0);
	close(msh->fdin);
	dup2(msh->fdout, 1);
	close(msh->fdout);
}

void	ft_free_msh(t_msh *msh)
{
	t_msh	*tmp_msh;
	int		i;

	while (msh)
	{
		if (msh->argv)
		{
			i = -1;
			while (msh->argv[++i])
				free(msh->argv[i]);
			free(msh->argv);
		}
		if (msh->outfile)
			free(msh->outfile);
		if (msh->infile)
			free(msh->infile);
		tmp_msh = msh;
		msh = msh->next;
		free(tmp_msh);
	}
}

int	ft_exec(t_msh *msh, t_sup *sup)
{
	char	*com;
	char	*s;

	if (ft_if_builtin(msh))
		return (ft_builtin(msh, sup));
	com = ft_command(msh->argv[0], sup->env);
	if (com)
	{
		pid = fork();
		if (pid == 0)
		{
			execve(com, msh->argv, sup->env);
			perror("execve");
			exit(1);
		}
		waitpid(pid, &g_status, 0);
		pid = 0;
		free(com);
		if (!WEXITSTATUS(g_status))
			return (1);
		return (0);
	}
	s = ft_strjoin(msh->argv[0], ": command not found");
	ft_error(s, 127);
	free(s);
	return (1);
}

// void	ft_handler(int sig)
// {
// 	if (sig == SIGINT && !pid)
// 	{
// 		write(1, "\n", 1);
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// }

int	main(int argc, char **argv, char **env)
{
	char	*str;
	t_msh	*msh;
	int		tmpin;
	int		tmpout;
	t_sup	*sup;
	t_msh	*save_msh;

	g_status = 0;
	pid = 0;
	sup = malloc(sizeof(t_sup));
	env_cpy(env, sup);
	while (1)
	{
		// signal(SIGINT, ft_handler);
		signal(SIGQUIT, SIG_IGN);
		tmpin = dup(0);
		tmpout = dup(1);
		str = readline("minishell$ ");
		if (str == NULL)
			break ;
		if (*str != '\0')
			add_history(str);
		msh = ft_mshnew();
		save_msh = msh;
		if (!ft_parser(msh, str, sup->env))
		{
			while (msh)
			{
				ft_pipe(msh, tmpin, tmpout);
				ft_exec(msh, sup);
				msh = msh->next;
			}
		}
		dup2(tmpin, 0);
		dup2(tmpout, 1);
		close(tmpin);
		close(tmpout);
		free(str);
		ft_free_msh(save_msh);
	}
}
