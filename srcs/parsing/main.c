/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:28:49 by mpignet           #+#    #+#             */
/*   Updated: 2022/12/03 01:03:48 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int main(int ac, char **av, char **env)
{
	char *input;
	int i = 0;
	t_data *data;

	(void)av;
	(void)env;
	while (ac > 0)
	{

		input = readline("Minishell>");
		if (input && *input)
		{
			if (ft_strncmp(input,"exit",4)  == 0)
				return(free(input),destroy_struct(data), exit(0), 0);
			data = NULL;
			add_history(input);
			init_token_lst(input, &data);
			// init_args(&data, input);
			// get_env(env, data);
			// get_path(data);
		}
			while(data)
			{
	 			printf("%s\n", data->args[0]);
	 			data = data->next;
			}
		free(input);
		destroy_struct(data);
		i++;
	}
}


// MAIN DE TEST MAEL

/* int main(int ac, char **av, char **envp)
{
	int		i = -1;
	t_data	data;

	data.args = malloc (sizeof(char **) * ac - 1);
	while (++i < (ac - 1))
		data.args[i] = ft_strjoin_spec(data.args[i], av[i + 1]);
	data.is_builtin = 1;
	data.next = NULL;
	ft_exec(&data);
	return (0);
} */