/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 13:58:52 by rchau             #+#    #+#             */
/*   Updated: 2022/01/11 20:01:52 by rchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_no_command(t_msh *msh)
{
	char	*s;

	s = ft_strjoin(msh->argv[0], ": command not found");
	ft_error(s, 127);
	free(s);
}

char	*ft_command_dir(char *str, char **env)
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

int	has_command(char *path, char *str)
{
	DIR				*dirp;
	struct dirent	*rdir;

	dirp = opendir(path);
	if (!dirp)
		return (0);
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

char	*ft_command(char *str, char **env)
{
	char	*dir;
	char	*com;
	char	*tmp;

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

void	ft_free_path(char **path_list)
{
	int	i;

	i = -1;
	while (path_list[++i])
		free(path_list[i]);
	free(path_list);
}
