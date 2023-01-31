/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:48:43 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/31 14:44:13 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../libft/inc/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <errno.h>
# include <signal.h>

typedef struct s_tok
{
	char			*token;
	struct s_tok	*next;
}	t_tok;

typedef struct s_glob
{	
	int	g_status;
	int	g_stop;
}	t_glob;

extern t_glob	g_var;

typedef struct s_pipes
{
	int	pipe[2];
}		t_pipes;

typedef struct s_envp
{
	char			**var;
	struct s_envp	*next;
}		t_envp;

typedef struct s_data
{
	char			**args;
	char			**env;
	char			*is_heredoc;
	char			*cmd_path;
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
	struct stat		path_stat;
	struct s_data	*next;
}	t_data;

/*---------------------SIGNAL----------------------*/
void	handle_sigint(int sig);
void	setup_sigint_handler(void);
/*---------------------PARSING----------------------*/

int		is_sep(char c);
int		split_space(char *input, int i, t_tok **lst);
void	o_signal(t_data *data);
void	pars_token(t_tok *lst, t_data *data);
int		skip_quote(char *token, int i);
t_tok	*init_token_lst(char *input, t_data	**lst);

int		check_separator(char c);
int		is_separator(char c1, char c2);
int		skip_separator(char *token, int i);
int		skip_non_separator(char *token, int i);
int		has_a_sep(char *token);
int		countword(char *token);
int		countlen_word(char *token);
void	clean_token(t_tok **lst, t_data *data);

int		is_char_var(char c);
int		len_status(int status);
int		len_env(char *str, int i);
int		len_expanded(char *str, int len_env, t_data *data);
int		write_status(char *temp);
int		write_t_envp(int *len, t_envp *tmp, char *temp);
void	process_token(char *tk, int *i, char **temp);
int		expand_extension(t_tok *tmp, int *dbl, int *sq, t_data **data);
char	*expand_from(char *token, t_data *data);
void	expand(t_tok **lst, t_data **data);

int		verif_redir(t_tok **tok_lst, t_data **data);
int		verif_pipe(t_tok **tok_lst, t_data **data);
int		check_next_operator(t_tok *node, t_tok **tok_lst, t_data **data);

int		check_in_file(char *str, t_data *node, t_tok **lst, t_data **data);
int		check_out_file(char *str, t_data *node, t_tok **lst, t_data **data);
int		check_redir(t_tok **lst, t_tok **lst_node, t_data **data, t_data *node);
void	process_node_redir(t_tok *node, t_tok **lst);
void	process_redir(t_tok **lst, t_data **data);

void	process_node(t_tok **node, t_tok **lst);
void	one_node(t_tok **lst);
void	multi_node(t_tok **lst_node, t_tok **lst);
void	trigger_creation(int *i, t_tok *temp, t_data *data_tmp);
void	process_pipes(t_tok *temp, t_tok **lst, t_data *data_tmp);
void	fill_node_with_tok(t_tok **lst, t_data **data, t_envp *envir);

void	clean_quotes(t_tok **lst);

/*------------------------------linked_list_utils-------------------------*/
void	tok_del_one(t_tok *lst);
t_tok	*lstnew_token(char *content);
t_tok	*lstnew_token2(char *content);
void	lstadd_back_token(t_tok **lst, t_tok *new);
t_tok	*ft_lstlast_tok(t_tok *lst);

t_data	*ft_lstlast_arg(t_data *lst);
t_data	*lstnew_args(t_envp *envir);
void	lstadd_back_args(t_data **lst, t_data *new);
int		create_data_args(t_tok **lst, t_data **data);

/*-----------------------------------ERR/CLEAN--------------------------------*/

void	disp_error(t_tok **tok_lst, t_data **data, char *token);
void	clean_parsing(t_tok **lst, t_data **data);
void	ft_free_tok(t_tok **lst_tok);
void	free_structures(t_tok **lst, t_data **data);
/*---------------------------------------ENV---------------------------------*/

t_envp	*lstnew_env(char **content);
t_envp	*get_env(char **envi);
char	**parse_env(t_envp *envir);

/*--------------------------------------PATH---------------------------------*/

/*---------------------EXEC----------------------*/

int		ft_exec(t_data *data);

/*-------------------------------------BUILTINS-------------------------------*/

int		ft_echo(t_data *data);
int		ft_cd(t_data *data);
void	update_old_pwd_env(t_envp *envp, char *curr_pwd);
void	update_pwd_env(t_envp *envp);
void	cd_err_msg(char *str);
int		ft_pwd(t_data *data);
void	ft_env(t_data *data);
void	ft_exit(t_data *data);
int		ft_unset(t_data *data);
int		ft_export(t_data *data);
void	ft_show_export(t_envp *envp, t_data *data);
int		check_valid_identifier(char *str);
int		check_for_option_export(char *str);
int		count_equal_signs(char *arg);
int		ft_dble_array_len(char **array);

int		ft_check_plus(char *str);
char	*ft_strtrim_spec(char *s1, char const *set);
int		increment_var(t_envp *envp, t_envp *new, t_data *data);
/*-------------------------------------UTILS----------------------------------*/

t_envp	*ft_envpnew(char *var, char *value);
t_envp	*ft_envplast(t_envp *envp);
void	ft_envpadd_front(t_envp **envp, t_envp *new);
void	ft_envpadd_back(t_envp **envp, t_envp *new);
void	ft_envpclear(t_envp **envp);
char	*seek_pwd_in_env(t_envp *envp);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strcmp_spec(const char *s1, const char *s2);
int		ft_data_size(t_data *data);
char	*ft_get_path(t_data *data);
char	*ft_strjoin_free_s2(char *s1, char *s2);
int		check_cmd_empty(t_data *data);
/*-----------------------------------ERR/CLEAN--------------------------------*/

void	ft_wait(t_data *data);
void	ft_close_fds(t_data *data);
void	ft_close_pipes(t_data *data);
void	ft_free_close(t_data *data);
void	ft_free_dble_array(void **tab);
void	ft_free_data(t_data *data);
void	clean_exit(t_data *data, int err);
int		set_err_status(int nb);

void	msg_cmd_not_found(char *cmd);
void	msg_invalid_id(char *str, int i);
void	msg_invalid_option(char *str, int i);
void	msg_is_directory(char *str);
void	msg_perror(char *str);

int		check_if_dir(char *path, t_data *data);
/*--------------------------------FDS/HEREDOC-------------------------------*/

int		init_pipes(t_data *data);
int		redirect_fds(t_data *data);
int		ft_open_infile(t_data *data);
int		ft_open_outfile(t_data *data);
void	ft_heredoc(t_data *data);
void	setup_sigint_handler(void);

void	sig_ignore_all(void);
void	setup_sig_child(void);

#endif