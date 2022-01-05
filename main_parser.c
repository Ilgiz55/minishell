#include "minishell.h"

// int main(int argc, char **argv, char **env)
// {
// 	char *str;
// 	t_msh *msh;
// 	t_msh *tmp;
// 	int i;
// 	int j;
// 	int flag;

// 	while (1)
// 	{
// 		flag = 0;
// 		str = readline("minishell>");
// 		add_history(str);
// 		msh = ft_mshnew();
// 		if (ft_parser(msh, str, env))
// 			flag = 1;

// 		j = 1;
// 		while(msh && !flag)
// 		{
// 			printf("*** command %d ***\n", j);
// 			printf("argc: %d\n", msh->argc);
// 			i = 0;
// 			while(i <= msh->argc)
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