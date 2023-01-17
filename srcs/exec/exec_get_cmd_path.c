/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_get_cmd_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:12:30 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/17 13:49:01 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*ft_check_access(char *cmd, char **paths)
{
	char	*cmd_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (!cmd_path)
			return (perror("malloc"), NULL);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	msg_cmd_not_found(cmd);
	return (NULL);
}

static int	add_slash(char **paths)
{
	char	*tmp;
	int		i;

	i = -1;
	while (paths[++i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		if (!paths[i])
			return (perror("Malloc"), free(tmp), 1);
	}
	return (free(tmp), 0);
}

char	*ft_get_path(t_data *data)
{
	char	**paths;
	char	*cmd_path;
	t_envp	*tmp_env;

	tmp_env = data->envp;
	while (tmp_env)
	{
		if (ft_strnstr(tmp_env->var[0], "PATH=", 5))
			break ;
		tmp_env = tmp_env->next;
	}
	paths = ft_split(tmp_env->var[1], ':');
	if (!paths)
		return (NULL);
	if (add_slash(paths))
		return (ft_free_dble_array((void **)paths), NULL);
	cmd_path = ft_check_access(data->args[0], paths);
	if (!cmd_path)
		return (ft_free_dble_array((void **)paths), NULL);
	return (ft_free_dble_array((void **)paths), cmd_path);
}