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
	char	**args;
	t_envp	*envp;
	struct s_data *next;
}	t_data;

typedef	struct s_tok
{
	char* token;
	struct s_tok *next;
}	t_tok;



void	init_struct(t_data *data);
void	init_args(t_data **data, char *arg);
void	destroy_struct(t_data *data);
void	free_array(char** array);
/*---------------------------------------ENV---------------------------------*/

t_envp	*lstnew_env(char **content);
void	lstadd_back_env(t_envp **lst, t_envp *new);
void	get_env(char **envi, t_data *data);

/*--------------------------------------PATH---------------------------------*/
char	*get_path(t_data *data);

/*---------------------------------------LEX---------------------------------*/
int is_quote(char c);
int	is_in_quote(char *arg, int i);
#endif