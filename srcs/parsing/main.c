/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:28:49 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/02 16:07:56 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int main(int ac, char **av, char **env)
{
	char *input;
	int i = 0;
	t_data *data;
	t_tok	*lst;

	(void)av;
	(void)lst;
	t_envp *envir = get_env(env);
	print_env(envir);
	while (ac > 0)
	{

		input = readline("Minishell>");
		if (input && *input)
		{
			if (ft_strncmp(input,"exit",4)  == 0)
				return(free(input),destroy_struct(data), exit(0), 0);
			add_history(input);
			lst = init_token_lst(input, &data);
			clean_token(&lst);
			clean_quotes(&lst);
			//expand(&lst);
			print_tok_list(lst);
		}
		free(input);
		i++;
	}
}


// MAIN DE TEST MAEL

/* int main(int ac, char **av, char **envp)
{
	int		i = -1;
	t_data	*data;

	data = malloc (sizeof(t_data));
	get_env(envp, data);
	data->args = malloc (sizeof(char **) * ac - 1);
	while (++i < (ac - 1))
		data->args[i] = ft_strjoin_spec(data->args[i], av[i + 1]);
	data->is_builtin = 1;
	data->next = NULL;
	ft_exec(data);
	free(data);
	return (0);
} */