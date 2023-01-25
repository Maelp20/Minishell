/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_get_cmd_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:12:30 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/25 20:42:35 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	add_slash(char **paths, t_data *data)
{
	int		i;

	i = -1;
	while (paths[++i])
	{
		paths[i] = ft_strjoin_spec(paths[i], "/");
		if (!paths[i])
			return (perror("malloc"), clean_exit(data, set_err_status(1)), 1);
	}
	return (0);
}

static char	*ft_check_access(char *cmd, char **paths, t_data *data)
{
	char	*cmd_path;
	int		i;

	add_slash(paths, data);
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (!cmd_path)
		{
			perror("malloc");
			clean_exit(data, set_err_status(1));
		}
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	msg_cmd_not_found(cmd);
	return (NULL);
}

char	*ft_get_path(t_data *data)
{
	char	**paths;
	char	*cmd_path;
	t_envp	*tmp_env;
	int		found;

	found = 0;
	tmp_env = data->envp;
	while (tmp_env)
	{
		if (ft_strnstr(tmp_env->var[0], "PATH=", 5))
		{
			found = 1;
			break ;
		}
		tmp_env = tmp_env->next;
	}
	if (!found)
		return (msg_cmd_not_found(data->args[0]), NULL);
	paths = ft_split(tmp_env->var[1], ':');
	if (!paths)
		return (set_err_status(1), NULL);
	cmd_path = ft_check_access(data->args[0], paths, data);
	if (!cmd_path)
		return (ft_free_dble_array((void **)paths), NULL);
	return (ft_free_dble_array((void **)paths), cmd_path);
}
