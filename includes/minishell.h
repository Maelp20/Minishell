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
	char	*cmd;
	char	**path;
	t_envp	*envp;
	struct s_data *prev;
	struct s_data *next;
}	t_data;

/*---------------------------------------ENV---------------------------------*/

t_envp	*lstnew_env(char **content);
void	lstadd_back_env(t_envp **lst, t_envp *new);
void	get_env(char **envi, t_data *data);

/*--------------------------------------PATH---------------------------------*/
char	*check_access(t_data *data);
#endif