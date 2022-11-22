/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:28:49 by mpignet           #+#    #+#             */
/*   Updated: 2022/11/22 19:24:23 by mpignet          ###   ########.fr       */
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
			// init_args(&data, input);
			// get_env(env, data);
			// get_path(data);
			i = 0;
			while (input[i])
			{
				if (is_quote(input[i]))
				{
					printf("i main = %d\n", i);
					i += is_in_quote(input, i);
				}
				else
					i++;

				printf("i boucle %d\n", i);
			}

		}
			while(data)
			{
	 			printf("%s\n", data->cmd);
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
	int		i = 0;
	t_data	data;

	if (ac > 1)
	{
		data.args = malloc (sizeof(char **) * ac - 1);
		while (i < (ac - 1))
		{
			data.args[i] = ft_strjoin_spec(data.args[i], av[i + 1]);
			i++;
		}
	}
	ft_echo(&data);
	// ft_cd(&data);
	// ft_pwd(envp);
	// ft_env(envp);
	return (0);
} */