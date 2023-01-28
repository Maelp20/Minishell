/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [1]main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:28:49 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/29 00:04:52 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_glob	g_var;

char	**parse_env(t_envp *envir)
{
	t_envp	*temp;
	int		i;
	char	**envi;

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

void	init_data(t_data **data, t_envp *envi)
{
	*data = ft_calloc(1, sizeof(t_data));
	if (!data)
		ft_free_data(*data);
	(*data)->envp = envi;
	(*data)->env = parse_env((*data)->envp);
	(*data)->fds = ft_calloc(1, sizeof(t_pipes));
}

void	verif_quotes(char *input, t_data *data, t_envp *envir)
{
	int	i;
	int	dbl;
	int	sgl;

	i = 0;
	dbl = 0;
	sgl = 0;
	while (input[i])
	{
		if (input[i] == '\"' && sgl % 2 == 0)
			dbl++;
		if (input[i] == '\'' && dbl % 2 == 0)
			sgl++;
		i++;
	}
	if (dbl % 2 != 0 || sgl % 2 != 0)
	{
		printf("minishell: syntax error: unexpected end of file\n");
		ft_free_data(data);
		free (input);
		ft_envpclear(&envir);
		exit(0);
	}
}

void	parser(char *input, t_data **data)
{
	t_tok	*lst;

	lst = init_token_lst(input, data);
	clean_token(&lst);
	expand(&lst, data);
	clean_quotes(&lst);

}

void	prompt(t_envp *envir)
{
	t_data	*data;
	char	*input;
	
	setup_sigint_handler();
	while (1)
	{
		init_data(&data, envir);
		input = readline("Minishell> ");
		if (input == 0)
		{
			printf("exit\n");
			exit(0);
		}
		if (input && *input)
		{
			verif_quotes(input, data, envir);
			parser(input, &data);
			add_history(input);
		}
		free(input);
		input = NULL;
	}
}

int	main(int ac, char **av, char **env)
{
	t_envp	*envir;

	(void)av;
	(void)ac;
	envir = get_env(env);
	if (!envir)
		return (ft_envpclear(&envir), 0);
	g_var.g_stop = 0;
	prompt(envir);
	ft_envpclear(&envir);
}
