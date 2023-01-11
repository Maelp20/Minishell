/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:28:49 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/11 01:00:11 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	init_data(t_data **data, t_envp *envi)
{
	*data = ft_calloc(1, sizeof(t_data));
	if (!data)
		printf("free blahblah\n");
	(*data)->envp = envi;
	(*data)->fds = ft_calloc(1, sizeof(t_pipes));
	//print_env((*data)->envp);
}





int main(int ac, char **av, char **env)
{
	char *input;
	int i = 0;
	t_data *data;
	t_tok	*lst;

	(void)av;
	data = NULL;
	t_envp *envir = get_env(env);
	//print_env(envir);
	while (ac > 0)
	{
		init_data(&data,envir);

		input = readline("Minishell>");
		if (input && *input)
		{
			// if (ft_strncmp(input,"exit",4)  == 0)
			// 	return(free(input),destroy_struct(data_ptr), exit(0), 0);
			add_history(input);
			lst = init_token_lst(input, &data);
			clean_token(&lst);
			clean_dquotes(&lst);
			expand(&lst, &data);
			clean_squotes(&lst);
			fill_node_with_tok(&lst, &data);
			//print_tok_list(lst);
		}
		free(input);
		i++;
	}
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
