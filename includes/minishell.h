#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_envp
{
	char 	**var;
	struct	s_envp *next;
}	t_envp;

typedef struct s_data
{
	t_envp	envp;
	char	*path;
	char	*cmd;
	struct s_data *prev;
	struct s_data *next;
}	t_data;


#endif