NAME	=	minishell
#NAME_B	=	minishell_bonus

HEADER	=	minishell.h
#HEADER_B	= ./bonus/minishell.h


SRC		= 	dollar.c		errors.c		ft_cd.c		\
			ft_echo.c		ft_env.c		ft_exit.c	\
			ft_export.c		ft_pwd.c		ft_unset.c	\
			main.c			utils.c			parser.c	\
			parser_utils.c	quotes.c		redirect.c	\
			support_fun.c	builtin.c		exec.c		\
			parser_utils_2.c	
#SRC_B	=	./

OBJS	=	$(SRC:.c=.o)
#OBJS_B	=	$(SRC_B:.c=.o)

RLIB	=	-L/Users/rchau/.brew/Cellar/readline/8.1.1/lib/
RINCL	=	-I/Users/rchau/.brew/Cellar/readline/8.1.1/include
RLINE	=	-lreadline
GCC		=	gcc -g
RM		=	rm -f
CFLAGS	=	-Werror -Wextra -Wall

all		:	$(NAME)


.c.o:
		$(GCC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS) $(HEADER)
		$(MAKE) -C ./libft
		$(GCC) $(CFLAGS) $(OBJS) ./libft/libft.a -o $(NAME) $(RLINE) $(RLIB) $(RINCL)

#bonus	:	$(OBJS_B) $(HEADER_B)
#		$(MAKE) -C ./libft
#		$(GCC) $(CFLAGS) $(OBJS_B) ./libft/libft.a -o $(NAME_B) $(RLINE) $(RLIB) $(RINCL)

clean:
		$(MAKE) clean -C ./libft
		$(RM) $(OBJS)
		$(RM) $(OBJS_B)

fclean	:	clean
		$(MAKE) fclean -C ./libft
		$(RM) $(NAME)
		$(RM) $(NAME_B)

re		:	fclean all

.PHONE	:	all clean fclean
