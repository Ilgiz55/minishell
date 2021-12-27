#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_msh
{

	int		argc;
	char	**argv;
	char	op;   // '|'   NULL
	int		fdin;
	int		fdout;
	struct s_msh *next;
}	t_msh;


#endif


