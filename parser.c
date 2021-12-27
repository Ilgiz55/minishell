#include "minishell.h"

void	ft_quotes(char **s, int *k)
{
	int j;
	int i;
	char *tmp[4];
	char *str;

	j = *k;
	i = *k;
	str = *s;
	while(str[++i])
		if (str[i] == '\'')
			break;
	// if (str[i] == '\0')
	// 		exit(printf("error\n"));
	tmp[0] = ft_substr(str, 0, j++);
	tmp[1] = ft_substr(str, j, i - j);
	tmp[2] = ft_strdup(str + i + 1);
	tmp[3] = ft_strjoin(tmp[0], tmp[1]);
	str = ft_strjoin(tmp[3], tmp[2]);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
	free(tmp[3]);
	free(*s);
	*k = i - 1;
	*s = str;
}

char *ft_get_env(char **env, char *key)
{
	int i;
	int j;
	char *answer;

	i = -1;
	while(env[++i])
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
				break;
			}
			free(answer);
		}
	}
	return (ft_substr(env[i], j + 1, ft_strlen(env[i]) - j));
}

void	ft_dollar(char **s, int *k, char **env)
{
	int j;
	int i;
	char *tmp[5];
	char *str;

	j = *k;
	i = *k;
	str = *s;
	while(str[++i])
		if (str[i] != '_' && !ft_isalnum(str[i]))
			break;
	if (i == j + 1)
		return ;
	j++;
	tmp[0] = ft_substr(str, j, i - j);
	tmp[1] = ft_get_env(env, tmp[0]);
	tmp[2] = ft_substr(str, 0, j - 1);
	tmp[3] = ft_strdup(str + i);
	tmp[4] = ft_strjoin(tmp[2], tmp[1]);
	str = ft_strjoin(tmp[4], tmp[3]);
	*k = i-1;
	j = -1;
	while (++j < 5)
		free(tmp[j]);
	free(*s);
	*s = str;
}

void	ft_slesh(char **s, int *k)
{
	int i;
	int j;
	char *tmp[3];
	char *str;

	i = *k;
	str = *s;
	tmp[0] = ft_substr(str, 0 , i);
	tmp[1] = ft_strdup(str + i +1);
	str = ft_strjoin(tmp[0], tmp[1]);
	*k = i + 1;
	free(tmp[0]);
	free(tmp[1]);
	free(*s);
	*s = str;
}

void ft_double_quotes(char **s, int *k, char **env)
{
	int j;
	int i;
	char *tmp[4];
	char *str;

	j = *k;
	i = *k;
	str = *s;
	while(str[++i])
	{
		if (str[i] == '\\' && (str[i + 1] == '\"' || str[i + 1] || str[i + 1] == '$' || str[i + 1] == '\\'))
			ft_slesh(&str, &i);
		if (str[i] == '$')
			ft_dollar(&str, &i, env);
		if (str[i] == '\"')
			break;	
	}
	// if (str[i] == '\0')
	// 		exit(printf("error\n"));
	tmp[0] = ft_substr(str, 0, j);
	j++;
	tmp[1] = ft_substr(str, j, i - j);
	tmp[2] = ft_strdup(str + i + 1);
	tmp[3] = ft_strjoin(tmp[0], tmp[1]);
	str = ft_strjoin(tmp[3], tmp[2]);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
	free(tmp[3]);
	// free(*s);
	*k = i-1;
	*s = str;
}

t_msh *ft_mshnew()
{
	t_msh *element;

	element = (t_msh *)malloc(sizeof(*element));
	element->argc = 0;
	element->op = 0;
	element->fdin = 0;
	element->fdout = 1;
	element->next = NULL;
	return(element);
}

int ft_error(char *str)
{
	printf("%s\n", str);
	return(1);
}

int ft_skip_space(char *str, int i)
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
	if (str[i] == '|')
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
	int j;
	char *file_name;

	j = *i;
	while (str[*i] && (str[*i] != ' ' && str[*i] != '|'))
		*i += 1;
	file_name = ft_substr(str, j, *i - j);
	return (file_name);
}

char *ft_get_stop_word(char *str, int *k)
{
	int i;
	int j;
	char *stop_word;

	i = *k;
	j = *k;
	while (str[i] && str[i] != '|' && str[i] != '>' && str[i] != '<' && str[i] != ' ')
		i++;
	stop_word = ft_substr(str, j, i -j);
	return (stop_word);
}

int	ft_redirect(t_msh *msh, char *str, int i)
{
	char *file_name;
	char *stop_word;
	char *s;
	char c;

	c = str[i];
	if (str[i] == '>')
	{
		if (str[++i] == '>')
		{
			c = str[i];
			i = ft_skip_space(str, ++i);
			if (str[i] == '<' || str[i] == ';' || str[i] == '|' || str[i] == '\0')
				exit(ft_error("syntax error"));
			file_name = ft_get_file_name(str, &i);
			msh->fdout = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
			free(file_name);
		}
		else
		{
			c = str[i];
			i = ft_skip_space(str, i);
			if (str[i] == '<' || str[i] == ';' || str[i] == '|' || str[i] == '\0')
				exit(ft_error("syntax error"));
			file_name = ft_get_file_name(str, &i);
			msh->fdout = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			free(file_name);
		}
	}
	else
	{
		if (str[++i] == '<')
		{
			c = str[i];
			i = ft_skip_space(str, ++i);
			c = str[i];
			if (str[i] == '>' || str[i] == '<' || str[i] == ';' || str[i] == '|' || str[i] == '\0')
				exit(ft_error("syntax error"));
			stop_word = ft_get_stop_word(str, &i);
			i++;
			s = readline(">");
			while (1)
			{
				if (!ft_strncmp(stop_word, s, ft_strlen(stop_word)))
				{
					free(s);
					free(stop_word);
					break;
				}
				free(s);
				s = readline(">");
			} 
		}
		else
		{
			c = str[i];
			i = ft_skip_space(str, i);
			if (str[i] == '>' || str[i] == ';' || str[i] == '|' || str[i] == '\0')
				exit(ft_error("syntax error"));
			i++;
			file_name = ft_get_file_name(str, &i);
			msh->fdin = open(file_name, O_RDONLY, 0644);
			free(file_name);
			if (msh->fdin < 0)
				exit(ft_error("no file"));
		}
	}
	return (i);
}

int ft_arg_len(char *str, int i)
{
	int j;
	
	j = i;
	while(str[i] && (str[i] != ' ' && str[i] != '|' && str[i] != '>' && str[i] != '<'))
	{
		if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"')
				i++;
		}
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
		}
		i++;
	}
	return (i - j);
}

char *ft_open_quotes(char *str, char **env)
{
	int i;
	char *tmp;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			ft_quotes(&str, &i);
		if (str[i] == '\\')
			ft_slesh(&str, &i);
		if (str[i] == '\"')
			ft_double_quotes(&str, &i, env);
		if (str[i]  == '$')
			ft_dollar(&str, &i, env);
	}
	return(str);
}

t_msh	*ft_new_command(t_msh *msh, char *str, int *k)
{
	int i;

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
	int	i;
	int n;
	t_msh *msh;
	t_msh *save_msh;

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



int main(int argc, char **argv, char **env)
{
	char *str;
	t_msh *msh;
	t_msh *tmp;
	int i;
	int j;
	while (1)
	{
		str = readline("minishell>");
		add_history(str);
		msh = ft_parser(str, env);

		j = 1;
		while(msh)
		{
			printf("*** command %d ***\n", j);
			printf("argc: %d\n", msh->argc);
			i = 0;
			while(i < msh->argc)
			{
				printf("argv[%d]: %s\n", i, msh->argv[i]);
				free(msh->argv[i]);
				i++;
			}
			free(msh->argv);
			printf("op: %c\n", msh->op);
			printf("fdin: %d, fdout: %d\n", msh->fdin, msh->fdout);
			tmp = msh;
			msh = msh->next;
			free(tmp);
			j++;
		}
		free(str);
	}
	return (0);
}

