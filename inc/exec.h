/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:48:43 by mpignet           #+#    #+#             */
/*   Updated: 2022/11/14 17:39:27 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "../libft/inc/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_envp {
	
	char	**var;
	struct s_envp *next;
}		t_envp;

typedef struct s_data
{
	char	*cmd;
	char	**args;
	t_envp	*envp;
	struct s_data *next;
}	t_data;

/* typedef struct s_exp {
	
	int		index;
	char	**var;
	struct s_exp *next;
}		t_exp; */

int		ft_echo(t_cmd *cmd);
int		ft_cd(t_cmd *cmd, t_envp *envp);
int		ft_pwd(t_cmd *cmd, t_envp *envp);
void	ft_env(t_envp *envp);
int		ft_unset(t_cmd *cmd, t_envp *envp);

t_envp	*ft_envpnew(char *var, char *value);
t_envp	*ft_envplast(t_envp *envp);
void	ft_envpadd_front(t_envp **envp, t_envp *new);
void	ft_envpadd_back(t_envp **envp, t_envp *new);
char	*seek_var_in_env(t_envp *envp, char *var);
char 	*seek_pwd_in_env(t_envp *envp);

int		ft_strcmp(const char *s1, const char *s2);

#endif