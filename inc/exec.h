/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:48:43 by mpignet           #+#    #+#             */
/*   Updated: 2022/11/17 16:29:59 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "../libft/inc/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef	struct s_tok
{
	char* token;
	struct s_tok *next;
}	t_tok;

typedef struct s_pipes
{	
	int	pipe1[2];
	int	pipe2[2];
}		t_pipes;

typedef struct s_envp 
{	
	char	**var;
	struct s_envp *next;
}		t_envp;

/*
Data struct changes :
- I put *cmd_path back in the struct but I'm still not sure if we can check for access during parsing,
or if I must do it for each cmd right before executing;
- If there are pipes before and/or after the command, we fill the "fds" t_pipes struct using the pipe function,
 and put 0 or 1 in "in_pipe" and "out_pipe" just to say "there is a pipe";
- If there is a file to read from, I think we open it in "in_fd" / Same with a file to write to, we open it in "out_fd";
 */

typedef struct s_data
{
	char			**args;
	char			*cmd_path;
	
	t_envp			*envp;
	t_pipes			*fds;
	pid_t			pid;
	
	int				is_builtin;
	int				in_fd;
	int				out_fd;
	int				in_pipe;
	int				out_pipe;
	int				is_append;
	struct s_data	*next;
}	t_data;

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
int		ft_data_size(t_data *data);





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