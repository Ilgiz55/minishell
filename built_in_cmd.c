#include "minishell.h"

int	ft_built_in_cmd(t_valu *values, char **argv)
{
//	if (!ft_strncmp(argv[0], "echo\0", 5))
//		ft_echo(argv);
//	else if (!ft_strncmp(argv[0], "pwd\0", 4))
//		ft_pwd();
	if (!ft_strncmp(argv[0], "env\0", 4))
		ft_env(values->env, argv);
	if (!ft_strncmp(argv[0], "export\0", 7))
		ft_export(values, argv);
//	if (!ft_strncmp(argv[0], "unset\0", 6))
//		ft_unset(argv, env);
//	if (!ft_strncmp(argv[0], "cd\0", 3))
//		ft_cd(argv, env);
//	if (!ft_strncmp(argv[0], "exit\0", 5))
//		ft_exit(argv, env);
//	else
//		return (0);
	return (0);
}