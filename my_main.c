#include "minishell.h"

void ft_builtin(t_msh *msh, char **env)
{
	printf("here will be the result of builtin command\n");
}

int ft_if_builtin(t_msh *msh)
{
	int i;
	char **b_com;
	
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
		if (!ft_strncmp(msh->argv[0], b_com[i], ft_strlen(msh->argv[0]) | ft_strlen(b_com[i])))
			return (1);
		i++;
	}
	return (0);
}

char *ft_command_dir(char *str, char **env)
{
	char	**path_list;
	DIR		*dirp;
	struct dirent *rdir;
	int		i;

	path_list = ft_split(ft_get_env(env, "PATH"), ':');
	i = -1;
	while(path_list[++i])
	{
		dirp = opendir(path_list[i]);
		rdir = readdir(dirp);
		while (rdir)
		{
			if (!ft_strncmp(rdir->d_name, str, ft_strlen(rdir->d_name) | ft_strlen(str)))
			{
				closedir(dirp);
				return (path_list[i]);
			}
			rdir = readdir(dirp);
		}
		closedir(dirp);
	}
	return (NULL);
}

char *ft_command(char *str, char **env)
{
	char *dir;
	char *com;
	char *tmp;
	int i;

	if (str[0] == '.' && str[1] == '/')
		return (str);
	dir = ft_command_dir(str, env);
	if (!dir)
		return (NULL);
	tmp = ft_strjoin(dir, "/");
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

void	ft_exec(t_msh *msh, char **env)
{
	char	*com;

	com = ft_command(msh->argv[0], env);
	if (ft_if_builtin(msh))
		ft_builtin(msh, env);
	else if (com)
	{
		msh->pid = fork();
		if (msh->pid == 0)
		{
			execve(com, msh->argv, env);
			perror("execve");
			exit(1);
		}
		waitpid(msh->pid, NULL, 0);
	}
	else
		printf("%s: command not found\n", msh->argv[0]);
}

int main(int argc, char **argv, char **env)
{
	char *str;
	t_msh *msh;
	int tmpin;
	int tmpout;

	while(1)
	{
		tmpin = dup(0);
		tmpout = dup(1);
		str = readline("mini$ ");
		if (*str != '\0')
			add_history(str);
		msh = ft_mshnew();

		if (!ft_parser(msh, str, env))
		{
			while(msh)
			{
				ft_pipe(msh, tmpin, tmpout);
				ft_exec(msh, env);
				msh = msh->next;
			}
		}
		dup2(tmpin, 0);
		dup2(tmpout, 1);
		close(tmpin);
		close(tmpout);
		free(str);
	}
}