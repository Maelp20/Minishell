/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [1]main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:28:49 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/23 00:31:28 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int g_status = 0;

void print_tout_huehue(t_data **data)
{
	t_data *temp;
	int i;

	temp = *data;
	while (temp)
	{
		i = -1;
		while (temp->args[++i])
			printf("data->args[%d] %s\n", i, temp->args[i]);
		i = -1;
		// while (temp->env[++i])
		// printf("data->env[%d] %s\n",i, temp->env[i]);
		printf("data->cmd_path %s\n", temp->cmd_path);
		printf("data->is_heredoc %s\n", temp->is_heredoc);
		printf("data->infile %s\n", temp->infile);
		printf("data->outfile %s\n", temp->outfile);
		// print_env(temp->envp);
		printf("is_builtin %d\n", temp->is_builtin);
		printf("is_append %d\n", temp->is_append);
		printf("in_fd %d\n", temp->in_fd);
		printf("out_fd %d\n", temp->out_fd);
		printf("in_pipe %d\n", temp->in_pipe);
		printf("out_pipe %d\n", temp->out_pipe);
		temp = temp->next;
	}
}

char **parse_env(t_envp *envir)
{
	t_envp *temp;
	int i;
	char **envi;

	i = 0;
	temp = envir;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	envi = ft_calloc((i + 1), sizeof(char *));
	if (!envi)
		ft_free_dble_array((void **)envi);
	temp = envir;
	i = 0;
	while (temp)
	{
		envi[i] = ft_strjoin(temp->var[0], temp->var[1]);
		i++;
		temp = temp->next;
	}
	envi[i] = NULL;
	return (envi);
}

void init_data(t_data **data, t_envp *envi)
{
	*data = ft_calloc(1, sizeof(t_data));
	if (!data)
		printf("free blahblah\n");
	(*data)->envp = envi;
	(*data)->env = parse_env((*data)->envp);
	(*data)->fds = ft_calloc(1, sizeof(t_pipes));
}

int main(int ac, char **av, char **env)
{
	char *input;
	int i = 0;
	t_data *data;
	t_tok *lst;

	(void)av;
	data = NULL;
	t_envp *envir;

	envir = get_env(env);
	if (!envir)
		return (ft_envpclear(&envir), 0);
	// print_env(envir);
	while (ac > 0)
	{
		init_data(&data, envir);
		input = readline("Minishell>");
		if (input && *input)
		{
			add_history(input);
			lst = init_token_lst(input, &data);
			clean_token(&lst);
			expand(&lst, &data);
			// print_tok_list(lst);
			clean_quotes(&lst);
			if (lst)
			{
				verif_pipe(&lst, &data);
				verif_redir(&lst, &data);
			}
			if(lst)
			{
				fill_node_with_tok(&lst, &data, envir);
				ft_exec(data);
				
			}
		i++;
		}
		free(input);
	}
	ft_free_data(data);
	ft_envpclear(&envir);
}

// int main(int ac, char **av, char **env)
// {
// 	char *input;
// 	int i = 0;
// 	t_data *data;
// 	t_tok	*lst;

// 	(void)av;
// 	(void)lst;
// 	t_envp *envir = get_env(env);
// 	data = NULL;
// 	while (ac > 0)
// 	{
// 		init_data(&data,envir);
// 		input = readline("Minishell>");
// 		if (input && *input)
// 		{
// 			add_history(input);
// 			char **result = ft_split(input, ' ');
// 			data->args = result;
// /* 			int i = 0;
// 			while (data->args[i])
// 			{
// 				printf("%s\n", data->args[i]);
// 				i++;
// 			} */
// 			ft_exec(data);
// 		}
// 		free(input);
// 		i++;
// 	}
// }
