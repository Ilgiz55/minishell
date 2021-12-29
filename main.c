#include "minishell.h"

void	parser(t_msh *op, char **argv)
{
	int k;
	int i;
	int n;
	int l;
	int j[3];


	i = 1;
	k = 0;
	while (argv[i])
	{
		if (ft_strchr("|<>\0", argv[i][0]))
			j[k++] = i;
		i++;
	}
	j[k] = i;
	i = 0;
	k = 1;
	n = 0;
	while (i != 3 && argv[k])
	{
		l = 0;
		op[i].argv = malloc(sizeof(char *) * (j[n]));
		while (k <= j[n] && argv[k])
		{
			if (!ft_strchr("|", argv[k][0]))
			{

				op[i].argv[l] = argv[k];
			}
			else
				op[i].op = argv[k][0];
			l++;
			k++;
		}
		if (op[i].op)
		{
			op[i].argc = l - 1;
			op[i].argv[l - 1] = NULL;
		}
		else
		{
			op[i].argc = l;
			op[i].argv[l] = NULL;
		}
		if (i > 0)
			op[i - 1].next = &(op[i]);
		i++;
		n++;
	}
//	op[i].next = NULL;
}

void env_cpy(char **env, t_valu *values)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	values->env = (char **)malloc(sizeof(char *) * (i + 1));
	values->env[i] = NULL;
	while (--i >= 0)
	{
		values->env[i] = ft_strdup(env[i]);
		if (!values->env[i])
		{
			exit_status = error_malloc();
			exit (exit_status);
		}
	}
}

int baby_process(t_valu *values, char **argv)
{
	if (ft_built_in_cmd(values, argv))
		return (0);
	return (1);
}

int parent_process(t_valu *values, t_msh *op, int i)
{
	exit (0);
}

void fd_create(t_valu *values)
{
	int i;
	int (*fd)[2];

	i = 0;
	values->pipe_cou = 0;
	values->pipe_fd = 0;
	values->fd = NULL;
	while (values->op[i].next)
	{
		if (values->op[i].op == '|')
			values->pipe_cou++;
		i++;
	}
	fd = malloc(sizeof(fd[2]) * values->pipe_cou);
	values->fd = fd;
}

int main(int argc, char **argv, char **env)
{
	int i;
	t_msh	*op;
	t_valu	values;

	i = 0;
	values.pipe_cou = 0;
	env_cpy(env, &values);
	op = (t_msh *)malloc(sizeof(t_msh) * 3);
	parser(op, argv);
	values.op = op;
	fd_create(&values);
	while (i < 3)
	{
		pipe(values.fd[values.pipe_fd]);
		op[i].pid = fork();
		if (op[i].pid != 0)
			baby_process(&values, op[i].argv);
		else
			parent_process(&values, op, i);
		i++;
	}
//	if (values.fd)
//	{
//		while (values.pipe_cou--)
//		{
//			close(values.fd[values.pipe_cou][0]);
//			close(values.fd[values.pipe_cou][1]);
//		}
//		free(values.fd);
//	}
	return 0;
}
