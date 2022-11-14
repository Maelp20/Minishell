/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:28:49 by mpignet           #+#    #+#             */
/*   Updated: 2022/11/14 18:28:50 by mpignet          ###   ########.fr       */
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