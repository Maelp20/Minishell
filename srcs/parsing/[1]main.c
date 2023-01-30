/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [1]main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:28:49 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/30 02:23:44 by yanthoma         ###   ########.fr       */
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
		ft_envpclear(&envir);
		free (input);
		exit(0);
	}
}

void	prompt(char *input, t_tok *lst, t_data *data, t_envp *envir)
{
	input = readline("Minishell> ");
	if (input == 0)
		o_signal(data);
	if (input && *input)
	{
		add_history(input);
		verif_quotes(input, data, envir);
		lst = init_token_lst(input, &data);
		pars_token(lst, data);
		if (lst)
		{
			if (verif_pipe(&lst, &data) == 0 && verif_redir(&lst, &data) == 0)
			{
				fill_node_with_tok(&lst, &data, envir);
				ft_exec(data);
			}
		}
		else
			ft_free_data(data);
	}
	else
		ft_free_data(data);
	free(input);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_data	*data;
	t_tok	*lst;
	t_envp	*envir;

	(void)av;
	data = NULL;
	lst = NULL;
	input = NULL;
	envir = get_env(env);
	if (!envir)
		return (ft_envpclear(&envir), 0);
	while (ac > 0)
	{
		setup_sigint_handler();
		g_var.g_stop = 0;
		init_data(&data, envir);
		prompt(input, lst, data, envir);
	}
	printf("salut\n");
	ft_free_data(data);
	ft_envpclear(&envir);
}
