/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:28:49 by mpignet           #+#    #+#             */
/*   Updated: 2022/12/19 15:04:19 by yanthoma         ###   ########.fr       */
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
	(void)env;
	while (ac > 0)
	{

		input = readline("Minishell>");
		if (input && *input)
		{
			if (ft_strncmp(input,"exit",4)  == 0)
				return(free(input),destroy_struct(data), exit(0), 0);
			data = malloc(sizeof(t_data));
			data = NULL;
			add_history(input);
			lst = init_token_lst(input, &data);
			clean_token(&lst);

			// init_args(&data, input);
			//get_env(env, data);
			// get_path(data);
		}
		// while(data->envp)
		// {
		// printf("%s%s\n", data->envp->var[0],data->envp->var[1] );
		// data->envp = data->envp->next;
		// }
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