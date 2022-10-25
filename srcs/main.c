/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:42:05 by mpignet           #+#    #+#             */
/*   Updated: 2022/10/25 16:45:13 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

char	*ft_strjoin_spec(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*dest;

	if (!s1)
	{
		s1 = malloc(sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s2)
		return (NULL);
	dest = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dest)
		return (NULL);
	i = -1;
	while (s1[++i])
		dest[i] = s1[i];
	j = 0;
	while (s2[j])
		dest[i++] = s2[j++];
	dest[i] = '\0';
	return (dest);
}

int main(int ac, char **av, char **envp)
{
	int		i = 0;
	t_lst cmd;

	if (ac > 1)
	{
		cmd.args = malloc (sizeof(char **) * ac - 1);
		cmd.cmd_name = av[1];
		while (i < (ac - 1))
		{
			cmd.args[i] = ft_strjoin_spec(cmd.args[i], av[i + 1]);
			i++;
		}	
	}
	// ft_echo(&cmd);
	// ft_cd(&cmd);
	// ft_pwd(envp);
	// ft_env(envp);
	return (0);
}