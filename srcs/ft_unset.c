/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:10:01 by mpignet           #+#    #+#             */
/*   Updated: 2022/10/25 18:23:25 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

char *seek_var_in_env(char **envp, char *var)
{
	char	*var_line;
	char	*needle;
	int		i;

	i = 0;
	needle = ft_strjoin(var, "=");
	if (!needle || !envp)
		return (NULL);
	while (envp[i])
	{
		var_line = ft_strnstr(envp[i], needle, 4);
		if (var_line)
		{
			var_line = ft_substr(envp[i], 4, ft_strlen(envp[i]));
			if (!var_line)
				return (perror("Malloc"), NULL);
			break ;
		}
		i++;
	}
	return (var_line);
}

int	ft_unset(t_lst *cmd, char **envp)
{
	char	*line;

	line = seek_var_in_env(envp, cmd->args[1]);
	if (!line)
		return (1);
	// need to modify env next... use export ?
}