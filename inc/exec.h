/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:48:43 by mpignet           #+#    #+#             */
/*   Updated: 2022/11/16 17:54:17 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "../libft/inc/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef	struct s_tok
{
	char* token;
	struct s_tok *next;
}	t_tok;

typedef struct s_envp {
	
	char	**var;
	struct s_envp *next;
}		t_envp;

typedef struct s_data
{
	char	*cmd;
	char	**args;
	t_envp	*envp;
	pid_t	pid;
	int		is_builtin;
	int		in_fd;
	int		out_fd;
	int		in_pipe;
	int		out_pipe;
	int		is_append;
	struct s_data	*next;
}	t_data;

/* typedef struct s_exp {
	
	int		index;
	char	**var;
	struct s_exp *next;
}		t_exp; */

int		ft_echo(t_data *data);
int		ft_cd(t_data *data);
int		ft_pwd(t_data *data);
void	ft_env(t_data *data);
int		ft_unset(t_data *data);
void	ft_export(t_data *data);
void	ft_exit(t_data *data);

t_envp	*ft_envpnew(char *var, char *value);
t_envp	*ft_envplast(t_envp *envp);
void	ft_envpadd_front(t_envp **envp, t_envp *new);
void	ft_envpadd_back(t_envp **envp, t_envp *new);
char	*seek_var_in_env(t_envp *envp, char *var);
char 	*seek_pwd_in_env(t_envp *envp);

int		ft_strcmp(const char *s1, const char *s2);






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