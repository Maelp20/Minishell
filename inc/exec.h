/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:48:43 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/03 19:10:53 by yanthoma         ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/wait.h>

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
- I will check for access for each cmd right before executing, and put the correct path in *cmd_path;
- If there are pipes before and/or after the command, in_pipe = 1 and/or out_pipe = 1.
	I will pipe accordingly using the t_pipes fds struct;
- If there is a file to read from or to, you must fill *infile and/or *outfile with their names.
	I will open them in "in_fd" and/or "out_fd";
- If there is a heredoc, put the limiter in *is_heredoc, I will create it during exec.
 */

typedef struct s_data
{
	char			**args;
	char			*cmd_path;
	char			*is_heredoc;
	char			*infile;
	char			*outfile;
	
	t_envp			*envp;
	t_pipes			*fds;
	pid_t			pid;
	
	int				is_builtin;
	int				is_append;
	int				in_fd;
	int				out_fd;
	int				in_pipe;
	int				out_pipe;
	int				size;
	struct s_data	*next;
}	t_data;

		/*---------------------PARSING----------------------*/
void print_tok_list(t_tok *list);

t_tok	*lstnew_token(char *content);
void	lstadd_back_token(t_tok **lst, t_tok *new);
t_tok	*ft_lstlast_tok(t_tok *lst);
t_tok	*init_token_lst(char *input, t_data	**lst);

int		is_sep(char c);
int		split_dbq(char *input, int i, t_tok **lst);
int		split_sq(char *input, int i, t_tok **lst);
int		split_space(char *input, int i, t_tok **lst);

int		is_to_split(char c);
void	replace_node(t_tok **lst, t_tok **tmp, t_tok *node);
int		split_pipe_and_chev(char *token, t_tok **lst);
void	clean_token(t_tok **lst);
void 	clean_quotes(t_tok **lst);

void	split_lst_operator(t_tok **tok_lst, t_data **lst);

void	expand(t_tok **lst, t_data **data);

/*---------------------------------------INIT---------------------------------*/
void	init_struct(t_data *data, char **envi);
t_data	*ft_lstlast_arg(t_data *lst);
t_data	*lstnew_args(char *content);
void	lstadd_back_args(t_data **lst, t_data *new);
void	destroy_struct(t_data *data);
void	free_array(char** array);
/*---------------------------------------ENV---------------------------------*/
void print_env(t_envp *list);
t_envp	*lstnew_env(char **content);
 void	lstadd_back_env(t_envp **lst, t_envp *new);
t_envp	*get_env(char **envi);

/*--------------------------------------PATH---------------------------------*/

/*---------------------------------------LEX---------------------------------*/
int is_quote(char c);

/*---------------------EXEC----------------------*/

int ft_exec(t_data *data);

/*-------------------------------------BUILTINS-------------------------------*/

int		ft_echo(t_data *data);
int		ft_cd(t_data *data);
int		ft_pwd(t_data *data);
void	ft_env(t_data *data);
int		ft_unset(t_data *data);
void	ft_export(t_data *data);
void	ft_exit(t_data *data);

/*-------------------------------------UTILS----------------------------------*/

t_envp	*ft_envpnew(char *var, char *value);
t_envp	*ft_envplast(t_envp *envp);
void	ft_envpadd_front(t_envp **envp, t_envp *new);
void	ft_envpadd_back(t_envp **envp, t_envp *new);
char 	*seek_pwd_in_env(t_envp *envp);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_data_size(t_data *data);

/*-----------------------------------ERR/CLEAN--------------------------------*/

void	exit_error(char *err, t_data *data);
void	ft_close_fds(t_data *data);
void	ft_free_close(t_data *data);
void	ft_close_pipes(t_data *data);
void	ft_free_dble_array(void **tab);
void	ft_wait(t_data *data);

/*---------------------------------OPEN/HEREDOC-------------------------------*/

void	ft_open_infile(t_data *data);
void	ft_open_outfile(t_data *data);

#endif