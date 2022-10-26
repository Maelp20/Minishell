#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_env
{
	char 	**env;
	struct	s_env *next;
}	t_env;

typedef struct s_data
{
	t_env	envp;
	char	*path;
	char	*cmd;
	struct s_data *prev;
	struct s_data *next;
}	t_data;


#endif