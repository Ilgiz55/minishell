#include "minishell.h"

void	ft_free_tmp(char **tmp, int n)
{
	while (n--)
		free(tmp[n]);
}

void	ft_quotes(char **s, int *k)
{
	int		j;
	int		i;
	char	**tmp;
	char	*str;

	j = *k;
	i = *k;
	tmp = (char **)malloc(sizeof(char *) * 4);
	str = *s;
	while (str[++i])
		if (str[i] == '\'')
			break ;
	tmp[0] = ft_substr(str, 0, j++);
	tmp[1] = ft_substr(str, j, i - j);
	tmp[2] = ft_strdup(str + i + 1);
	tmp[3] = ft_strjoin(tmp[0], tmp[1]);
	str = ft_strjoin(tmp[3], tmp[2]);
	ft_free_tmp(tmp, 4);
	free(*s);
	*k = i - 1;
	*s = str;
}

char	*ft_get_env(char **env, char *key)
{
	int		i;
	int		j;
	char	*answer;

	i = -1;
	while (env[++i])
	{
		if (ft_strnstr(env[i], key, ft_strlen(env[i])))
		{
			j = 0;
			while (env[i][j] && env[i][j] != '=')
				j++;
			answer = ft_substr(env[i], 0, j);
			if (ft_strncmp(key, answer, ft_strlen(key)) == 0)
			{
				free(answer);
				break ;
			}
			free(answer);
		}
	}
	return (ft_substr(env[i], j + 1, ft_strlen(env[i]) - j));
}

void	ft_dollar(char **s, int *j, char **env)
{
	int		i;
	char	**tmp;
	char	*str;

	i = *j;
	str = *s;
	tmp = (char **)malloc(sizeof(char *) * 5);
	while (str[++i])
		if (str[i] != '_' && !ft_isalnum(str[i]))
			break ;
	if (i == ++(*j))
		return ;
	tmp[0] = ft_substr(str, *j, i - *j);
	tmp[1] = ft_get_env(env, tmp[0]);
	tmp[2] = ft_substr(str, 0, *j - 1);
	tmp[3] = ft_strdup(str + i);
	tmp[4] = ft_strjoin(tmp[2], tmp[1]);
	str = ft_strjoin(tmp[4], tmp[3]);
	*j = i - 1;
	ft_free_tmp(tmp, 5);
	free(*s);
	*s = str;
}

void	ft_slesh(char **s, int *j)
{
	int		i;
	char	*tmp;
	char	*tmp1;
	char	*str;

	i = *j;
	str = *s;
	tmp = ft_substr(str, 0, i);
	tmp1 = ft_strdup(str + i + 1);
	str = ft_strjoin(tmp, tmp1);
	*j = i + 1;
	free(tmp);
	free(tmp1);
	free(*s);
	*s = str;
}

int	ft_dollar_in_double_quotes(char **env, char **s, int *i)
{
	char	*str;

	str = *s;
	if (str[*i] == '\\' && (str[*i + 1] == '\"' || str[*i + 1] || \
		str[*i + 1] == '$' || str[*i + 1] == '\\'))
	{
		(*i)++;
		ft_slesh(s, i);
	}
	if (str[*i] == '$')
		ft_dollar(s, i, env);
	return (++(*i));
}

void	ft_double_quotes(char **s, int *j, char **env)
{
	int		i;
	char	**tmp;
	char	*str;
	char	c;

	i = *j + 1;
	tmp = (char **)malloc(sizeof(char *) * 4);
	while (*(*s+i) != '\"')
		i = ft_dollar_in_double_quotes(env, s, &i);
	str = *s;
	tmp[0] = ft_substr(str, 0, (*j)++);
	tmp[1] = ft_substr(str, *j, i - *j);
	tmp[2] = ft_strdup(str + i + 1);
	tmp[3] = ft_strjoin(tmp[0], tmp[1]);
	str = ft_strjoin(tmp[3], tmp[2]);
	ft_free_tmp(tmp, 4);
	free(*s);
	*j = i - 1;
	*s = str;
}

t_msh	*ft_mshnew(void)
{
	t_msh	*element;

	element = (t_msh *)malloc(sizeof(*element));
	element->argc = 0;
	element->op = 0;
	element->fdin = 0;
	element->fdout = 1;
	element->next = NULL;
	return (element);
}

int	ft_error(char *str)
{
	printf("%s\n", str);
	return (1);
}

int	ft_skip_space(char *str, int i)
{
	while (str[i] == ' ')
		i++;
	return (i);
}

int	ft_check_start(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '|' || str[i] == ';')
		exit(ft_error("syntax error"));
	return (i);
}

int	ft_argc(char *str, int i)
{
	int	n;

	n = 0;
	while (str[i] && str[i] != '|')
	{
		while (str[i] == ' ')
			i++;
		while (str[i] && (str[i] != ' '))
		{
			if (str[i] == '\"')
				while (str[++i] != '\"')
					;
			if (str[i] == '\'')
				while (str[++i] != '\'')
					;
			i++;
		}
		n++;
	}
	return (n);
}

char	*ft_get_file_name(char *str, int *i)
{
	int		j;
	char	*file_name;

	j = *i;
	while (str[*i] && (str[*i] != ' ' && str[*i] != '|'))
		*i += 1;
	file_name = ft_substr(str, j, *i - j);
	return (file_name);
}

char	*ft_get_stop_word(char *str, int *j)
{
	int		i;
	char	*stop_word;

	i = *j;
	while (str[i] && str[i] != '|' && str[i] != '>' \
		&& str[i] != '<' && str[i] != ' ')
		i++;
	stop_word = ft_substr(str, *j, i - *j);
	return (stop_word);
}

void	ft_redirect_output(char *str, int *j, t_msh *msh, int flag)
{
	char	*file_name;
	int		i;

	i = *j;
	i = ft_skip_space(str, ++i);
	if (str[i] == '<' || str[i] == ';' || str[i] == '|' || str[i] == '\0')
		exit(ft_error("syntax error"));
	file_name = ft_get_file_name(str, &i);
	if (flag == 2)
		msh->fdout = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		msh->fdout = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(file_name);
	*j = i;
}

void	ft_stop_word(char *str, int *j, t_msh *msh)
{
	char	*stop_word;
	char	*new_word;
	int		i;

	i = *j;
	i = ft_skip_space(str, ++i);
	if (str[i] == '>' || str[i] == '<' || str[i] == ';' || \
		str[i] == '|' || str[i] == '\0')
		exit(ft_error("syntax error"));
	stop_word = ft_get_stop_word(str, &i);
	i++;
	new_word = readline(">");
	while (1)
	{
		if (!ft_strncmp(stop_word, new_word, \
			ft_strlen(stop_word) + ft_strlen(new_word)))
		{
			free(new_word);
			free(stop_word);
			*j = i;
			break ;
		}
		free(new_word);
		new_word = readline(">");
	}
}

void	ft_redirect_input(char *str, int *j, t_msh *msh)
{
	char	*file_name;
	int		i;

	i = *j;
	i = ft_skip_space(str, i);
	if (str[i] == '>' || str[i] == ';' || str[i] == '|' || str[i] == '\0')
		exit(ft_error("syntax error"));
	i++;
	file_name = ft_get_file_name(str, &i);
	msh->fdin = open(file_name, O_RDONLY, 0644);
	free(file_name);
	if (msh->fdin < 0)
		exit(ft_error("no file"));
	*j = i;
}

int	ft_redirect(t_msh *msh, char *str, int i)
{
	if (str[i] == '>')
	{
		if (str[++i] == '>')
			ft_redirect_output(str, &i, msh, 2);
		else
			ft_redirect_output(str, &i, msh, 1);
	}
	else
	{
		if (str[++i] == '<')
			ft_stop_word(str, &i, msh);
		else
			ft_redirect_input(str, &i, msh);
	}
	return (i);
}

int	ft_arg_len(char *str, int i)
{
	int	j;

	j = i;
	while (str[i] && (str[i] != ' ' && str[i] != '|' && \
		str[i] != '>' && str[i] != '<'))
	{
		if (str[i] == '\"')
			while (str[++i] != '\"')
				;
		if (str[i] == '\'')
			while (str[++i] != '\'')
				;
		i++;
	}
	return (i - j);
}

char	*ft_open_quotes(char *str, char **env)
{
	int		i;
	char	*tmp;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			ft_quotes(&str, &i);
		if (str[i] == '\\')
			ft_slesh(&str, &i);
		if (str[i] == '\"')
			ft_double_quotes(&str, &i, env);
		if (str[i] == '$')
			ft_dollar(&str, &i, env);
	}
	return (str);
}

t_msh	*ft_new_command(t_msh *msh, char *str, int *k)
{
	int	i;

	i = *k;
	msh->op = str[i];
	i++;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0' && str[i] != '|' && str[i] != '>' && str[i] != '<')
		exit(ft_error("pipe error"));
	msh->next = ft_mshnew();
	msh = msh->next;
	msh->argv = (char **)malloc(sizeof(char *) * ft_argc(str, i));
	*k = i;
	return (msh);
}

t_msh	*ft_parser(char *str, char **env)
{
	int		i;
	int		n;
	t_msh	*msh;
	t_msh	*save_msh;

	msh = ft_mshnew();
	save_msh = msh;
	i = ft_check_start(str);
	msh->argv = (char **)malloc(sizeof(char *) * ft_argc(str, i));
	while (str[i])
	{
		n = ft_arg_len(str, i);
		if (str[i] != ' ' && str[i] != '|' && str[i] != '>' && str[i] != '<')
			msh->argv[msh->argc++] = ft_open_quotes(ft_substr(str, i, n), env);
		i += n;
		i = ft_skip_space(str, i);
		if (str[i] == '>' || str[i] == '<')
			i = ft_redirect(msh, str, i);
		i = ft_skip_space(str, i);
		if (str[i] == '|')
			msh = ft_new_command(msh, str, &i);
	}
	return (save_msh);
}

// int main(int argc, char **argv, char **env)
// {
// 	char *str;
// 	t_msh *msh;
// 	t_msh *tmp;
// 	int i;
// 	int j;
// 	while (1)
// 	{
// 		str = readline("minishell>");
// 		add_history(str);
// 		msh = ft_parser(str, env);

// 		j = 1;
// 		while(msh)
// 		{
// 			printf("*** command %d ***\n", j);
// 			printf("argc: %d\n", msh->argc);
// 			i = 0;
// 			while(i < msh->argc)
// 			{
// 				printf("argv[%d]: %s\n", i, msh->argv[i]);
// 				free(msh->argv[i]);
// 				i++;
// 			}
// 			free(msh->argv);
// 			printf("op: %c\n", msh->op);
// 			printf("fdin: %d, fdout: %d\n", msh->fdin, msh->fdout);
// 			tmp = msh;
// 			msh = msh->next;
// 			free(tmp);
// 			j++;
// 		}
// 		free(str);
// 	}
// 	return (0);
// }
